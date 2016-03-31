import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

import "components/"


Window {
    width: screenWidth
    height: screenHeight

    property date curDate: new Date()
    property int textMargin: 10;
    property int borderSize: width/50
    property int lineHeight: width/18
    property int sectionLineHeight: width/25
    property int fontPixelSize: width/40
    property int buttonHeight: height/20
    property int backgroundImageIter: 0
    property int clockWidth: width/10
    Timer {
        interval: 10000; running: true; repeat: true;
        onTriggered:changeView()
    }
    Timer {
        interval: 5000; running: true; repeat: true;
        onTriggered:nextImage()
    }
    Timer {
        interval: 1000; running: true; repeat: true;
        onTriggered:clockTick()
    }

    function changeView() {
        if(forecastButton.checked)
            graphButton.checked = true;
        else
            forecastButton.checked = true;
    }
    function clockTick() {
        var date = new Date;

        clockText.text = ("0" + date.getHours()).slice(-2)+":"+("0" + date.getMinutes()).slice(-2)+":"+("0" + date.getSeconds()).slice(-2);
    }
    function nextImage() {
        if(nImages > 0)
        {
            var image = "file://"+imagesPath+"/images/img"+backgroundImageIter+".jpg";
            backgroundImage.source = image;
        }

        backgroundImageIter++;
        if(backgroundImageIter >= nImages)
            backgroundImageIter = 0;
    }

    visible: true
    Image {
        id:backgroundImage
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
            width: parent.width/2-clockWidth/2
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
            width: parent.width/2-clockWidth/2
            height: buttonHeight
            anchors.left: forecastButton.right
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
        Rectangle{
            id: clock;
            width: clockWidth
            height: buttonHeight
            anchors.right: parent.right
            color: "transparent"
            Text{
                id:clockText
                width: parent.width
                height: parent.height
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                color: "black"
                font.bold: true
                font.pixelSize: fontPixelSize
                text: "Clock"
            }
            MouseArea {
                anchors.fill: parent
                onClicked: Qt.quit();
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
}
