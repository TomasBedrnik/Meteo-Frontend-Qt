import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

import "components/"

Window {
    width: 640
    height: 480

    property int borderSize: width/50
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
        clip: true
        ListView {
            width: parent.width;
            model: myModel
            height: parent.height
            delegate:
                Rectangle {
                width:parent.width
                height:parent.width/8
                color: "transparent"
                Text {
                    id: t;
                    height:parent.height
                    verticalAlignment: Text.AlignVCenter
                    text: time
                }
                WeatherIcon{
                    id:cloudImageId
                    anchors.left: t.right
                    pictureFile: cloudImage
                    pictureText: cloudText
                }

                WeatherIcon{
                    anchors.left: cloudImageId.right
                    pictureFile: windImage
                    pictureText: windText
                }
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
