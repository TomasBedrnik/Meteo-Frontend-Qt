import QtQuick 2.5
import QtQuick.Window 2.2

Window {
    width: 640
    height: 480

    property int borderSize: width/50
    visible: true
    Image {
        width: parent.width
        height: parent.height
        fillMode: Image.PreserveAspectCrop
        source: "/background/default.jpg"
    }
    Rectangle {
        id: leftForecast
        width: parent.width/2-(borderSize*2)
        height: parent.height-(borderSize*2)
        color: "#44FFFFFF"
        anchors.margins: borderSize
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
    }

    Rectangle {
        id: rightForecast
        width: parent.width/2-(borderSize*2)
        height: parent.height-(borderSize*2)
        color: "#44FFFFFF"
        anchors.margins: borderSize
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
    }
    MouseArea {
        anchors.fill: parent
        onClicked: {
            Qt.quit();
        }
    }
}
