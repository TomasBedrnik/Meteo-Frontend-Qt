import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Image {
    property string pictureFile
    property string pictureText
    anchors.verticalCenter: parent.verticalCenter
    width:parent.height-5
    height:parent.height-5
    source: pictureFile
    Rectangle {
        height:parent.height
        width:toolTipText.contentWidth+10
        anchors.left: parent.horizontalCenter
        anchors.bottom: parent.verticalCenter
        color:"#66FFFFFF"
        Text {
            id: toolTipText
            height:parent.height
            width:parent.width
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            text: pictureText
        }
        visible: mouseArea.containsMouse
    }
    MouseArea {
        id: mouseArea
        hoverEnabled: true
        anchors.fill: parent
    }
}
