import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Rectangle{
    property int radarImageIter: 0
    anchors.fill: parent
    color:"transparent"
    Timer {
        interval: 1000; running: true; repeat: true;
        onTriggered:nextRadar()
    }
    function nextRadar() {
        var nGraphs = 12;
        var d = new Date;
        var dateAct = new Date(d.getTime() - (nGraphs - radarImageIter)*600000)
        var date = new Date(d.getTime() + d.getTimezoneOffset()*60000 - (nGraphs - radarImageIter)*600000)
        var minutes = Math.floor(date.getMinutes()/10)*10;
        radar.text = ("0" + dateAct.getHours()).slice(-2)+":"+("0" + minutes).slice(-2);

        radarImg.source = "file://"+imagesPath+"/radarImages/radar"+date.getFullYear()+("0" + (date.getMonth()+1)).slice(-2)+("0" + date.getDate()).slice(-2)+"."+("0" + date.getHours()).slice(-2)+("0" + minutes).slice(-2)+".png";
        lightningImg.source = "file://"+imagesPath+"/radarImages/lightning"+date.getFullYear()+("0" + (date.getMonth()+1)).slice(-2)+("0" + date.getDate()).slice(-2)+"."+("0" + date.getHours()).slice(-2)+("0" + minutes).slice(-2)+".png";

        radarImageIter++;
        if(radarImageIter > nGraphs)
            radarImageIter = 0;
    }
    Image {
        width: parent.width
        height: parent.height
        fillMode: Image.PreserveAspectCrop
        sourceSize.width: parent.width
        sourceSize.height: parent.height
        source: "/images/mapa.jpg"
    }    
    Rectangle{
        anchors.fill: parent
        color:"transparent"
        Image {
            id: radarImg
            opacity: 0.8
            width: parent.width
            height: parent.height
            fillMode: Image.PreserveAspectCrop
            sourceSize.width: parent.width
            sourceSize.height: parent.height
            source: ""
        }

        Rectangle{
            anchors.fill: parent
            color:"transparent"
            Text {
                id: radar
                font.pixelSize: fontPixelSize
                text: "Radar Image Time"
            }
            Image {
                id: lightningImg
                width: parent.width
                height: parent.height
                fillMode: Image.PreserveAspectCrop
                sourceSize.width: parent.width
                sourceSize.height: parent.height
                source: ""
            }
        }
    }
}
