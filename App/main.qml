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
        TableView {
            id: myTable
            model: myModel
            headerVisible: false
            width: parent.width
            height: parent.height
            backgroundVisible: false
            alternatingRowColors: false
            style: TableViewStyle{
                backgroundColor: "transparent"
                alternateBackgroundColor: "transparent"
                textColor: "black"
                frame: Rectangle{
                    color: "transparent"
                    border{
                        color: "red"
                        width:0
                    }
                }
            }
            TableViewColumn {
                role: "type"
                title: "Type"
                width:myTable.width/2
            }
            TableViewColumn {
                role: "size"
                title: "Size"
                width:myTable.width/4
                delegate:
                    Image {
                    fillMode: Image.PreserveAspectFit
                    source: styleData.value === "" ? "/images/1.png" : "/images/"+styleData.value+".png"
                    //source: "/symbols/images/"+styleData.value+".png"
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
    //    MouseArea {
    //        anchors.fill: parent
    //        onClicked: {
    //            Qt.quit();
    //        }
    //    }

    //    ListModel {
    //        id: myModel
    //        ListElement {
    //            title: "item one"
    //        }
    //        ListElement {
    //            title: "item two"
    //        }
    //    }
}
