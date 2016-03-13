import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

import "components/"

Window {
    width: 640
    height: 480

    property int textMargin: 10;
    property int borderSize: width/50
    property int lineHeight: width/18
    property int fontPixelSize: width/40
    visible: true
    Image {
        width: parent.width
        height: parent.height
        fillMode: Image.PreserveAspectCrop
        source: "/images/background.jpg"
    }
    Rectangle {
        id: leftForecast
        width: parent.width/2-(borderSize*2)
        height: parent.height-(borderSize*2)
        color: "#44FFFFFF"
        anchors.margins: borderSize
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        //clip: true
        ListView {
            width: parent.width;
            model: myModel
            height: parent.height
            delegate:
                Rectangle {
                width:parent.width
                height:lineHeight
                color:"transparent"
                Loader{
                    source: section ? "components/WeatherSection.qml" : "components/WeatherLine.qml"
                    width:parent.width
                    height:lineHeight
                }

//                Text {
//                    id: timeID
//                    height:parent.height
//                    verticalAlignment: Text.AlignVCenter
//                    text: time
//                    font.pixelSize: fontPixelSize
//                }
//                Text {
//                    id: tempId
//                    anchors.right: precId.left
//                    width:parent.height*1.5
//                    height:parent.height
//                    verticalAlignment: Text.AlignVCenter
//                    horizontalAlignment: Text.AlignHCenter
//                    text: temperature
//                    font.bold: true
//                    font.pixelSize: fontPixelSize
//                }
//                Text {
//                    id: precId
//                    anchors.right: cloudImageId.left
//                    width:parent.height*2
//                    height:parent.height
//                    verticalAlignment: Text.AlignVCenter
//                    horizontalAlignment: Text.AlignHCenter
//                    text: precipitation
//                    font.pixelSize: fontPixelSize
//                }
//                WeatherIcon{
//                    id:cloudImageId
//                    anchors.right: windImageId.left
//                    pictureFile: cloudImage
//                    pictureText: cloudText
//                }

//                WeatherIcon{
//                    id: windImageId
//                    anchors.right: parent.right
//                    pictureFile: windImage
//                    pictureText: windText
//                }
            }
        }
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
}
