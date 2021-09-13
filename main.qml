import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 1.0
import cameraModel 1.0

ApplicationWindow {
    id: wd
    visible: true
    width: 640
    height: 480
    title: qsTr("Video Camera Streaming")
//    x: Screen.width / 2 - width / 2
//    y: Screen.height / 2 - height / 2

    Component.onCompleted: {
        x = Screen.width / 2 - width / 2
        y = Screen.height / 2 - height / 2
    }

    Camera{
        id: camera
        anchors.fill: parent
    }
}
