#include "cameraModel.h"
#include <QVideoFrame>

CameraModel::CameraModel(QQuickItem *parent)
    : QQuickPaintedItem(parent),
      m_disMode(DIS_VIDEO),
      m_resolution(RES_720x1280),
      m_fps(30),
      m_cameraState(CAM_UN_INIT),
      cameraWorker(NULL),
      m_image(NULL),
      m_cameraFrame(NULL),
      m_brightness(50),
      m_realFps(0)

{
    m_image = new QImage();
    cameraWorker = new cameraThread();
    connect(cameraWorker, &cameraThread::frameCaptured, this, &CameraModel::frameCapturedCallback);
    connect(cameraWorker, &cameraThread::captureLoopFinished, this, &CameraModel::captureLoopFinished);
    cameraWorker->start();
}

CameraModel::~CameraModel()
{
    cameraClose();
}

int CameraModel::cameraStart()
{
    if(cameraWorker->openDevice(m_deviceName, m_width, m_height, m_fps) < 0)
        return -1;

    cameraWorker->setState(THRD_RUN);
    m_cameraState = CAM_RUN;
    setDIsplayMode(DIS_VIDEO);
    return 0;
}

int CameraModel::cameraClose()
{
    if(cameraWorker)
        cameraWorker->closeDevice();
    m_cameraState = CAM_UN_INIT;
    setDIsplayMode(DIS_PAUSE);
    return 0;
}

int CameraModel::cameraIdle()
{
    if(m_cameraState == CAM_UN_INIT)
        return -1;

    m_cameraState = CAM_IDLE;
    cameraWorker->setState(THRD_IDLE);
    setDIsplayMode(DIS_PAUSE);
    return 0;
}

const char* CameraModel::deviceName()
{
    return m_deviceName.toStdString().c_str();
}


void CameraModel::frameCapturedCallback(CameraFrame_t* frame)
{
    if(frame->exception == ERROR)
        return;
    // MJEP pixel format
    mutex.lock();
    m_drawNow = true;
    m_cameraFrame = frame;
    mutex.unlock();
    this->update();
}

void CameraModel:: captureLoopFinished(void * arg)
{
    float fps = *((float*)arg);
    static float avr_fps = 0;
    static int counter = 0;
    const int nTime = 5;

    avr_fps += fps;
    if(++counter >= nTime)
    {
        fps = avr_fps / nTime;
        setRealFps((unsigned int)fps);
        counter = 0;
        avr_fps = 0;
    }
}

void CameraModel::paint(QPainter *painter)
{
    mutex.lock();

    QRect* imageBound;
    imageBound = new QRect(this->x(), this->y(), this->width(), this->height());

    if(m_disMode == (int)DIS_VIDEO)
    {
        if(m_drawNow)
        {
            m_drawNow =false;
            if(getCameraState() == CAM_RUN)
            {
                if(m_cameraFrame->buffer->start != NULL)
                    m_image->loadFromData((uchar*)m_cameraFrame->buffer->start, m_cameraFrame->buffer->length);
            }
        }
    }
    else if(m_disMode == (int)DIS_IMAGE)
    {
        m_image->load(getOpenImagePath());
        qDebug () << "Load new image " << getOpenImagePath();

    } else if(m_disMode == (int)DIS_PAUSE)
    {
        painter->drawText(QPoint(this->width()/2, this->height()/2), QString("PAUSE"));
    }
    else
    {
        qDebug("Unknown dispplay mode");
    }

    // for fullscreen mode
    if(m_isFullScreen){}

    if(m_image)
        painter->drawImage(*imageBound, *m_image);

    mutex.unlock();
}

/* Q_PROPERTY set function is implemented from here */
/* READ */
int CameraModel::getCameraState() const
{
    return m_cameraState;
}

ColorMode CameraModel::getColorMode() const
{
    return m_colorMode;
}

int CameraModel:: getImageWidth() const
{
    return m_width;
}

int CameraModel::getImageHeight() const
{
    return m_height;
}

QString CameraModel:: getDeviceName() const
{
    return m_deviceName;
}

unsigned int CameraModel::getFps() const
{
    return m_fps;
}

unsigned int CameraModel::getBrightness() const
{
    return m_brightness;
}

QString CameraModel::getResolution() const
{
    switch (m_resolution) {
    case RES_720x1280:
        return QString("1280x720") ;
        break;
    case RES_480x640:
        return QString("640x480") ;
        break;
    case RES_340x460:
        return QString("460x340") ;
        break;
    default:
        break;
    }
    return QString("");
}

unsigned int CameraModel::getRealFps() const
{
    return m_realFps;
}
/* WRITE */
void CameraModel::setCameraState(int state)
{
    switch (m_cameraState) {
    // set state from startup
    case CAM_UN_INIT:
        switch (state) {
        case CAM_IDLE:
            cameraIdle();
            break;
        case CAM_RUN:
            cameraStart();
            break;
        }
        break;
        // set state from idle mode
    case CAM_IDLE:
        switch (state) {
        case CAM_UN_INIT:
            cameraClose();
            break;
        case CAM_RUN:
            cameraStart();
            break;
        }
        break;
        // set state from run mode
    case CAM_RUN:
        switch (state) {
        case CAM_UN_INIT:
            cameraClose();
            break;
        case CAM_IDLE:
            cameraIdle();
            break;
        }
        break;
    }
}

void CameraModel::setColorMode(ColorMode colorMode) 
{
    if(m_colorMode != colorMode)
        m_colorMode = colorMode;
}

bool CameraModel::cameraTriggerCapture()
{
    qDebug("camera trigger capture\n");
    return m_isCapturing;
}

void CameraModel::setImageWidth(int w)
{
    if(m_width != w)
    {
        m_width = w;
        emit widthChanged();
    }
}

void CameraModel::setImageHeight(int h)
{
    if(m_height != h)
    {
        m_height = h;
        emit heightChanged();
    }
}

void CameraModel::setDeviceName(QString device)
{
    if(m_deviceName != device)
        m_deviceName = device;
}

void CameraModel::setFps(unsigned int fps)
{
    if(fps != m_fps){
        m_fps = fps;
        if(cameraWorker)
            m_fps = cameraWorker->setFps(m_fps);
    }
}

void CameraModel::setBrightness(unsigned int brightness)
{
    if(m_brightness != brightness)
        m_brightness = brightness;
}

void CameraModel::setRealFps(unsigned int fps)
{
    if(m_realFps!=fps)
    {
        m_realFps = fps;
        emit realFpsChanged();
    }
}
/* Function calling from UI */
void CameraModel::openImage()
{
    mutex.tryLock();
    setCameraState(CAM_UN_INIT);
    mutex.unlock();
}

void CameraModel::fullScreenMode(bool full)
{
    m_isFullScreen = full;

    if(m_isFullScreen)
    {
        window()->showFullScreen();
    }else
    {
        window()->showNormal();
    }
}

void CameraModel::captureImage()
{
    mutex.tryLock();
    QString fileName = QString("captured_image_%1.jpeg").arg(QDateTime::currentDateTime().toString());
    if(m_image){
        if(m_image->save(fileName) >=0)
            qDebug() << "Saving new image successfully, with name is: " << fileName;
    }
    mutex.unlock();
}

void CameraModel:: saveImageAccepted(const QUrl &url)
{
    mutex.tryLock();
    if(m_image)
        m_image->save(url.toString());
    mutex.unlock();
}

void CameraModel::openImageAccepted(const QUrl &url)
{
    mutex.tryLock();
    setCameraState(CAM_UN_INIT);
    if(!m_image) m_image = new QImage();
    setOpenImagePath(url.path());
    setDIsplayMode(DIS_IMAGE);
    mutex.unlock();
    this->update();
}

void CameraModel:: setDIsplayMode(int mode)
{
    m_disMode = mode;
}

void CameraModel::setOpenImagePath(QString s)
{
    m_imagePath = s;
}

QString CameraModel::getOpenImagePath()
{
    return m_imagePath;
}
