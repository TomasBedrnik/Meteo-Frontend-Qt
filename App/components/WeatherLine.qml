import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
Rectangle {

    color:"transparent"
    Text {
        id: timeID
        height:parent.height
        verticalAlignment: Text.AlignVCenter
        text: time
        font.pixelSize: fontPixelSize
    }
    Text {
        id: tempId
        anchors.right: precId.left
        width:parent.height*1.5
        height:parent.height
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        text: temperature
        font.bold: true
        font.pixelSize: fontPixelSize
    }
    Text {
        id: precId
        anchors.right: cloudImageId.left
        width:parent.height*2
        height:parent.height
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        text: precipitation
        font.pixelSize: fontPixelSize
    }
    WeatherIcon{
        id:cloudImageId
        anchors.right: windImageId.left
        pictureFile: cloudImage
        pictureText: cloudText
    }

    WeatherIcon{
        id: windImageId
        anchors.right: parent.right
        pictureFile: windImage
        pictureText: windText
    }
}
