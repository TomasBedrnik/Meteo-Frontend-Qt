import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Rectangle{
    anchors.fill: parent
    color:"#66FFFFFF"
    Image {
        width: parent.width
        height: parent.height
        fillMode: Image.PreserveAspectCrop
        sourceSize.width: parent.width
        sourceSize.height: parent.height
        source: "file:"+applicationDirPath+"/../../Meteo-Backend/graph.svg"
    }
}
