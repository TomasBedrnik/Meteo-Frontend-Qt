import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Rectangle{
    anchors.fill: parent
    color:"transparent"
    Rectangle {
        id: leftForecast
        width: parent.width/2-(borderSize*1.5)
        height: parent.height-(borderSize*2)
        color: "#44FFFFFF"
        anchors.margins: borderSize
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        clip: true
        ListView {
            width: parent.width;
            model: modelLeft
            height: parent.height
            delegate:
                Rectangle {
                width:parent.width
                height: section ? sectionLineHeight : lineHeight
                color:"transparent"
                Loader{
                    source: section ? "WeatherSection.qml" : "WeatherLine.qml"
                    width:parent.width
                    height: section ? sectionLineHeight : lineHeight
                }
            }
        }
    }

    Rectangle {
        id: rightForecast
        width: parent.width/2-(borderSize*1.5)
        height: parent.height-(borderSize*2)
        color: "#44FFFFFF"
        anchors.margins: borderSize
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        clip: true
        ListView {
            width: parent.width;
            model: modelRight
            height: parent.height
            delegate:
                Rectangle {
                width:parent.width
                height: section ? sectionLineHeight : lineHeight
                color:"transparent"
                Loader{
                    source: section ? "WeatherSection.qml" : "WeatherLine.qml"
                    width:parent.width
                    height: section ? sectionLineHeight : lineHeight
                }
            }
        }
    }
}
