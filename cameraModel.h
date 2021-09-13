#ifndef CAMERA_MODEL_H
#define CAMERA_MODEL_H

#include <QtQuick>
#include <QObject>
#include <QImage>
#include <QQuickPaintedItem>
#include "cameraThread.h"
#include <QList>
#include <QMutex>

enum ColorMode
{
    COL_NORMAL = 0,
    COL_GRAY,
    COL_BLACK_WHITE,
    COL_BLUE,
    COL_READ,
    COL_GREEN,
};

enum CameraModelState
{
    CAM_UN_INIT = -1,
    CAM_IDLE,
    CAM_RUN,
};

enum DisplayMode
{
    DIS_VIDEO = 0,
    DIS_IMAGE,
    DIS_PAUSE,
};

enum Resolution
{
    RES_720x1280 = 0,
    RES_480x640,
    RES_340x460,
};

class CameraModel : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(int imgWidth READ getImageWidth WRITE setImageWidth NOTIFY widthChanged)
    Q_PROPERTY(int imgHeight READ getImageHeight WRITE setImageHeight NOTIFY heightChanged)
    Q_PROPERTY(int cameraState READ getCameraState WRITE setCameraState)

    Q_PROPERTY(QString device READ getDeviceName WRITE setDeviceName)
    Q_PROPERTY(unsigned int fps READ getFps WRITE setFps)
    Q_PROPERTY(unsigned int brightness READ getBrightness  WRITE setBrightness)
    Q_PROPERTY(QString resolution READ getResolution)

    Q_PROPERTY(unsigned int realFps READ getRealFps WRITE setRealFps NOTIFY realFpsChanged)

private:
    int m_cameraState;
    bool m_isCapturing;
    ColorMode m_colorMode;
    cameraThread *cameraWorker;
    CameraFrame_t *m_cameraFrame;
    int m_disMode;
    QString m_imagePath;
    QImage *m_image = NULL;

    bool m_isFullScreen;
    unsigned int m_fps;
    unsigned int m_realFps;
    QString m_deviceName;
    unsigned int m_brightness;

    int m_width;
    int m_height;

    Resolution m_resolution;

    QList<QString> m_deviceList;
    QList<unsigned int> m_fpsList;
    QList<enum Resolution> m_resolutionList;

    QMutex mutex;
    bool m_drawNow = false;



public:
    explicit CameraModel(QQuickItem *parent = nullptr);
    virtual ~CameraModel();
    virtual void paint(QPainter *painter) override;


    const char* deviceName();
    /* READ */
    int getCameraState() const;
    ColorMode getColorMode() const;
    int getImageWidth() const;
    int getImageHeight() const;
    QString getDeviceName() const;
    unsigned int getFps() const;
    unsigned int getBrightness() const;
    QString getResolution() const;
    unsigned int getRealFps() const;
    /* WRITE */
    void setCameraState(int state);                           // switch between mode
    void setColorMode(ColorMode colorMode);              // set color mode
    bool cameraTriggerCapture();
    void setImageWidth(int w);
    void setImageHeight(int h);
    void setDeviceName(QString device);
    void setFps(unsigned int fps);
    void setBrightness(unsigned int brightness);
    void setRealFps(unsigned int fps);

public slots:
    void frameCapturedCallback(CameraFrame_t *frame);
    void captureLoopFinished(void * arg);
    /* UI */
    void fullScreenMode(bool full);
    int cameraStart();
    int cameraClose();
    int cameraIdle();
    void captureImage();
    void openImage();
    void openImageAccepted(const QUrl &url);

private slots:
    void saveImageAccepted(const QUrl &url);
    void setDIsplayMode(int mode);
    void setOpenImagePath(QString s);
    QString getOpenImagePath();

public:
    QStringList getVideoDeivceList();
    int* getVideoFps();



signals:
    void widthChanged();
    void heightChanged();
    void imageChanged();
    void realFpsChanged();
};

#endif // CAMERA_MODEL_H
