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
    property int sectionLineHeight: width/25
    property int fontPixelSize: width/40
    property int buttonHeight: height/20
    visible: true
    Image {
        width: parent.width
        height: parent.height
        fillMode: Image.PreserveAspectCrop
        source: "/images/background.jpg"
    }

    Rectangle {
        id: buttons
        width: parent.width
        height: buttonHeight
        anchors.top: parent.top
        color:"transparent";
        ExclusiveGroup {
            id: navButtons
        }
        Button{
            id: forecastButton;
            width: parent.width/2
            height: buttonHeight
            anchors.left: parent.left
            text: "Forecast"
            checkable:true
            checked:true
            exclusiveGroup: navButtons
            style:ButtonStyle{
                background:Rectangle{
                    color:control.checked ? "#4400FF00" : "#44FFFFFF"
                }
                label: Text{
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    color: "black"
                    font.bold: true
                    font.pixelSize: fontPixelSize
                    text: control.text
                }
            }
        }
        Button{
            id: graphButton;
            width: parent.width/2
            height: buttonHeight
            anchors.right: parent.right
            text: "Graph"
            checkable:true
            exclusiveGroup: navButtons
            style:ButtonStyle{
                background:Rectangle{
                    color:control.checked ? "#4400FF00" : "#44FFFFFF"
                }
                label: Text{
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    color: "black"
                    font.bold: true
                    font.pixelSize: fontPixelSize
                    text: control.text
                }
            }
        }

    }
    Rectangle {
        id: space
        width: parent.width
        height: parent.height-(buttonHeight)
        anchors.bottom: parent.bottom
        color:"transparent"

        Loader{
            anchors.fill: parent
            source: navButtons.current == forecastButton ? "components/WeatherForecast.qml" : "components/WeatherGraph.qml"
        }
    }
    //    MouseArea {
    //        anchors.fill: parent
    //        onClicked: Qt.quit();
    //        }
}
