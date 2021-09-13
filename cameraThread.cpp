#include "cameraThread.h"
#include <QElapsedTimer>
#include <QDebug>

cameraThread::cameraThread(QObject *parent)
    : QThread(parent),
      t_initializied(false),
      videodInput(NULL),
      t_state(THRD_IDLE)
{
}

cameraThread::cameraThread(QString device, int width, int height, unsigned int fps):
    t_fps(fps)
{
    this->openDevice(device, width, height, fps);
}

cameraThread::~cameraThread()
{
    closeDevice();
    this->disconnect(this);
    setState(THRD_QUICK);
    this->quit();
    qDebug("kill thread");
}

void cameraThread::run()
{
    QElapsedTimer timer;
    qint64 begintTime = 0;
    timer.start();
    int quick = 1;
    const int request_rate = 60;
    float real_fps;

    while (quick)
    {
        mutex.tryLock();
        // btryLock running task untill deivice is created
        if (!t_initializied)
            continue;

        begintTime = timer.nsecsElapsed();
        switch (t_state)
        {
        case THRD_IDLE:
            //qDebug("thread idle\n");
            break;

        case THRD_RUN:
            //qDebug("thread running\n");
            t_cameraFrame.exception = 0;
            if(v4l2_uvc_grab(videodInput) < 0 )
            {
                t_cameraFrame.exception = -1;
            }
            else{
                t_cameraFrame.buffer = v4l2_get_buffer(videodInput);
            }
            emit frameCaptured(&t_cameraFrame);
            break;

        case THRD_QUICK:
            quick = 0;
            break;
        default:
            break;
        }

        // t get frame calculated
        // loop delay_time = 1.000.000/fps - t (if t < 1.000.000/fps)
        // udelay(delay_time)

        t_captureDurationTime = (timer.nsecsElapsed() - begintTime)/1000;
        t_usDelayTime = 1000000 / request_rate - t_captureDurationTime;
        real_fps = (1000000.0 /t_captureDurationTime);
        if (t_usDelayTime > 0)
        {
            qDebug() << "capture time " << t_captureDurationTime << ", delay time "
                     << t_usDelayTime << " fps = " << request_rate;
            usleep(t_usDelayTime);
        }
        else {
            qDebug() << "real fps = " << real_fps;
        }

        emit captureLoopFinished(&real_fps);

        mutex.unlock();
    }
}

int cameraThread::closeDevice()
{
    int ret = -1;
    mutex.tryLock();
    t_initializied = false;
    t_state = THRD_IDLE;
    if(videodInput != NULL){
        ret = v4l2_viceo_capture_remove(videodInput);
        videodInput = NULL;
    }
err:
    mutex.unlock();
    return ret;
}

int cameraThread::openDevice(QString device)
{
    int ret = -1;
    mutex.tryLock();
    t_device = device;
    if (!t_initializied) {
        if (t_deviceIsOpen = CAMERA_INIT(videodInput, this->deviceName()) < 0){
            mutex.unlock();
            ret = -1;
            return ret;
        }

        else{
            t_initializied = true;
            ret = 0;
        }
    }
    else
    {
        closeDevice();
        openDevice(device);
    }

    mutex.unlock();
    return ret;
}

int cameraThread::openDevice(QString device, int width, int height, unsigned int fps) {
    int ret = -1;
    qDebug() << "open device\n";
    mutex.tryLock();
    t_device = device;
    t_width = width;
    t_height = height;
    t_fps = fps;
    if (t_deviceIsOpen = v4l2_video_capture_init(&videodInput, this->deviceName(),
                                                 t_width, t_height, DEFAULT_PIXEL_FORMAT,
                                                 DEFAULT_GRAB_METHOD, DEFAULT_NUM_BUFFER) < 0)
    {
        t_initializied = false;
    }
    else
        t_initializied = true;

    ret = t_initializied? 0 : -1;
    mutex.unlock();
    return ret;
}

int cameraThread::reOpenDevice()
{
    int ret=-1;
    mutex.tryLock();
    if(t_deviceIsOpen >=0)
    {
        if(t_initializied)
            closeDevice();
        t_deviceIsOpen = openDevice(t_device, t_width, t_height, t_fps);
        ret = t_deviceIsOpen;
    }
    mutex.tryLock();
    return ret;
}

int cameraThread::stopStreaming()
{
    mutex.tryLock();
    v4l2_dequeue_buffer(videodInput);
    int ret = video_stream_off(videodInput);
    mutex.unlock();
    return ret;
}

int cameraThread::startStreaming()
{
    mutex.tryLock();
    int ret = video_stream_on(videodInput);
    mutex.unlock();
    return ret;
}


bool cameraThread::isInitialized()
{
    mutex.tryLock();
    bool temp = t_initializied;
    mutex.unlock();
    return temp;

}

void cameraThread::setState(CameraState state)
{
    mutex.tryLock();
    if (state != (int)t_state)
        t_state = state;

    if(t_state == THRD_IDLE)
        closeDevice();
    mutex.unlock();
}

unsigned int cameraThread::setFps(unsigned int fps)
{
    int ret = 0;
    mutex.tryLock();

    t_fps = fps;
    if(t_fps == 0)
        t_fps = 1;
    // set fps to camera
    ret = t_fps;
    mutex.unlock();

    return t_fps;
}

unsigned int cameraThread::setBrightness(unsigned int bright)
{
    int ret = 0;
    mutex.tryLock();

    brightness = bright;
    int er = v4l2_set_ctrl(videodInput,V4L2_CID_BRIGHTNESS, brightness);
    if(er<0)
        ret = -1;
    else
        ret = t_fps;
    mutex.unlock();

    return ret;
}
