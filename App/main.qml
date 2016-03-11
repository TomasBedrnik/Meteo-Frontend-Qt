import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

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
//                WeatherIcon{
//                id: cloudImageId
//                }
                WeatherIcon{
                    id:cloudImageId
                    anchors.left: t.right
                    pictureFile: cloudImage
                    pictureText: cloudText
                }

//                Image {
//                    id:cloudImageId
//                    anchors.left: t.right
//                    anchors.verticalCenter: parent.verticalCenter
//                    width:parent.height-5
//                    height:parent.height-5
//                    source: "/images/clouds/"+cloudImage+".png"
//                    Rectangle {
//                        height:parent.height
//                        width:toolTipCloudText.contentWidth+10
//                        anchors.left: parent.horizontalCenter
//                        anchors.bottom: parent.verticalCenter
//                        color:"#66FFFFFF"
//                        Text {
//                            id: toolTipCloudText
//                            height:parent.height
//                            width:parent.width
//                            horizontalAlignment: Text.AlignHCenter
//                            verticalAlignment: Text.AlignVCenter
//                            text: cloudText
//                        }
//                        visible: mouseAreaCloud.containsMouse
//                    }
//                    MouseArea {
//                        id: mouseAreaCloud
//                        hoverEnabled: true
//                        anchors.fill: parent
//                    }
//                }
                Image {
                    anchors.left: cloudImageId.right
                    anchors.verticalCenter: parent.verticalCenter
                    width:parent.height-5
                    height:parent.height-5
                    source: "/images/wind/"+windImage+".png"
                    Rectangle {
                        height:parent.height
                        width:toolTipWindText.contentWidth+10
                        anchors.left: parent.horizontalCenter
                        anchors.bottom: parent.verticalCenter
                        color:"#66FFFFFF"
                        Text {
                            id: toolTipWindText
                            height:parent.height
                            width:parent.width
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            text: windText
                        }
                        visible: mouseAreaWind.containsMouse
                    }
                    MouseArea {
                        id: mouseAreaWind
                        hoverEnabled: true
                        anchors.fill: parent
                    }
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
