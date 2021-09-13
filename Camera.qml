import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3
import cameraModel 1.0
import QtQuick.Dialogs 1.1
import Qt.labs.platform 1.0

Item {
    anchors.fill: parent
    property string cam_fps: "fps: 30"
    property string cam_resolution: "size: 1280 x 720"
    property real cam_brightness: 60 ;
    property string foreground: "white"
    property string background: "black"

    Rectangle{
        id: root
        anchors.fill: parent
        color: background

        RowLayout{
            id: header
            transformOrigin: Item.Center
            anchors.top: parent.top;
            anchors.left: parent.left
            height: 10
            anchors.leftMargin: 5
            anchors.topMargin: 5
            spacing: 20

            Text {
                id: menu_file
                text: qsTr("File");
                color: qsTr(foreground);
            }

            Text {
                id: menu_camera
                text: qsTr("Camera");
                color: qsTr(foreground);
            }

            Text {
                id: menu_resolution
                text: qsTr("Resolution");
                color: qsTr(foreground);
            }

            Text {
                id: menu_about
                text: qsTr("About");
                color: qsTr(foreground);
            }
        }

        FileDialog{
            id: fileDialog
            title: "Please choose a file";
            nameFilters: ["Image Files (*.jpg *.png *.jpeg *.yuy)"];
            visible: false
            onAccepted: {
                camera.openImageAccepted(file)
                but_play.isOn = false;
                fileDialog.close()
            }
        }

        CameraModel
        {
            id: camera
            anchors.top: header.bottom
            anchors.bottom: footer.top
            anchors.right: parent.right
            anchors.left : parent.left
            imgHeight: 720
            imgWidth: 1280
            device: "/dev/video0"
            fps: 30
            cameraState: 0  //idle state
        }

        ColumnLayout{
            anchors.right: root.right
            anchors.top: root.top
            anchors.rightMargin: 10
            anchors.topMargin: 30
            property int fontsize: 10
            Text {
                id: txt_resolution
                text:  qsTr("size: %1x%2").arg(camera.imgWidth).arg(camera.imgHeight)
                font.pointSize: parent.fontsize
                color: foreground
            }
            Text {
                id: txt_fps
                text: qsTr("fps: %1 \\ %2").arg(camera.fps).arg(camera.realFps);
                font.pointSize: parent.fontsize
                color: foreground
            }
        }

        Rectangle{
            id: footer
            height: 45
            width: parent.width
            anchors.bottom: parent.bottom
            color:"lightgray"

            RowLayout{
                anchors.fill: parent

                ImageButton {
                    id: but_play
                    anchors.leftMargin: 10
                    anchors.left: parent.left
                    onImage: "pause.png"
                    offImage: "play.png"
                    imageSource: "play.png"
                    stateMode: true
                    height: 40
                    width: 40
                    onButtonClick: {
                        if(btnState)
                            camera.cameraState = 1;
                        else
                            camera.cameraState = 0;

                        if(camera.cameraState === -1)
                        {
                            but_play.isOn = false;
                        }
                    }
                }

                ImageButton {
                    id: but_capture
                    anchors.leftMargin: 20
                    anchors.left :but_play.right
                    imageSource: "capture.png"
                    height: 40
                    width: 40
                    onButtonClick: {
                        camera.captureImage();
                    }
                }

                ImageButton{
                    id:btn_open
                    anchors.leftMargin: 20
                    anchors.left :but_capture.right
                    height: 40;
                    width:40
                    imageSource: "open.png"
                    onButtonClick: {
                        if(fileDialog.visible != true)
                            fileDialog.open();
                    }
                }
                RowLayout
                {
                    spacing: 5
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    anchors.left: btn_open.right
                    anchors.leftMargin: 40
                    anchors.rightMargin: 100

                    Text {
                        id:txt_bright
                        text: qsTr("Brightness")
                    }
                    Slider {
                        id: brightness
                        anchors.left: txt_bright.right
                        anchors.leftMargin: 10
                        implicitWidth: 200
                        value: camera.brightness
                        maximumValue: 100
                        orientation: Qt.Horizontal
                        enabled: false
                        onValueChanged:
                        {
                            console.log(value)
                        }
                    }

                    Text {
                        anchors.right: parent.right
                        anchors.left: brightness.right
                        anchors.leftMargin: 10

                        text: qsTr("%1/%2").arg(brightness.value).arg(brightness.maximumValue);
                        font.pointSize: 10
                    }
                }

                ImageButton{
                    property bool isFull: false
                    anchors.right: parent.right
                    height: 45;
                    width:45
                    imageSource: "fullscreen.png"
                    onButtonClick: {
                        isFull = !isFull;
                        camera.fullScreenMode(isFull);
                    }
                }
            }
        }
    }
}
