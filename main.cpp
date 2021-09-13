#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "cameraModel.h"
#include <QQmlContext>
#include <QMenu>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    //qmlRegisterUncreatableType<const MyClass>("Test", 1, 0, "MyClass", "Don't create it");

    qmlRegisterType<CameraModel>("cameraModel", 1,0, "CameraModel");

    QQmlApplicationEngine engine;

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
