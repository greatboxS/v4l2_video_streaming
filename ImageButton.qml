import QtQuick 2.0

Item {
    property string onImage: ""
    property string offImage: ""
    property bool isOn: false
    signal buttonClick(var btnState);
    property string imageSource: ""
    property bool stateMode: false
    property bool isHover: false
    Image {
        anchors.fill: parent
        id: but_open
        height: parent.height
        width: parent.width
        source: getImage()
        scale: !isHover? 0.8 : 1

        MouseArea{
            anchors.fill: parent
            hoverEnabled: true;
            onHoveredChanged: {
                isHover = !isHover;
            }

            onClicked: {
                if(stateMode)
                {
                    isOn = !isOn;
                    imageSource = isOn? onImage : offImage
                }
                buttonClick(isOn);
            }
        }

        function getImage()
        {
            if(stateMode)
            {
                imageSource = isOn? onImage : offImage
            }
            return imageSource;
        }
    }
}
