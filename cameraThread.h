#ifndef V4L2_CAMERA_THREAD_H
#define V4L2_CAMERA_THREAD_H

#include <QThread>
#include <QColor>
#include <QList>
#include "uvccapture/v4l2uvc.h"
#include <QMutex>

enum CameraState
{
    THRD_IDLE = 0,
    THRD_RUN,
    THRD_QUICK,
} ;

enum CaptureExeption{
    ERROR = -1,
    SUCCESS = 0,
};

typedef struct {
    int exception;
    struct mem_buffer* buffer;
} CameraFrame_t;

class cameraThread : public QThread
{
    Q_OBJECT
private:
    enum CameraState t_state;
    bool t_initializied = false;
    int t_deviceIsOpen = -1;
    qint64 t_usDelayTime;
    unsigned int t_fps = 30;
    qint64 t_captureDurationTime;
    QString t_device;
    struct vdIn *videodInput = NULL;
    CameraFrame_t t_cameraFrame;

    bool stopStream=false;
    int t_width, t_height, brightness;

    QMutex mutex;

    const char* deviceName()
    {
        static char t_deviceName[128];
        memset(t_deviceName, 0, sizeof(t_deviceName));
        snprintf(t_deviceName, sizeof(t_deviceName), "%s", t_device.toStdString().c_str());
        return t_deviceName;
    }

    int stopStreaming();
    int startStreaming();


public:
    cameraThread(QObject *parent = Q_NULLPTR);
    cameraThread(QString device, int width, int height, unsigned int fps);
    
    ~cameraThread();
    void run() override;

    int closeDevice();
    int openDevice(QString device, int width, int height, unsigned int fps);
    int openDevice(QString device);
    int reOpenDevice();
    bool isInitialized();
    unsigned int setFps(unsigned int fps);
    unsigned int setBrightness(unsigned int bright);

public slots:
    void setState(CameraState state);

signals:
    void frameCaptured(CameraFrame_t *camFrame);
    void captureLoopFinished(void * arg);
};

#endif // V4L2_CAMERA_H
