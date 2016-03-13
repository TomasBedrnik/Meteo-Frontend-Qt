import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
Rectangle {
    color: "#44FFFFFF"
    Text {
        id: timeID
        height:parent.height
        verticalAlignment: Text.AlignVCenter
        text: date
        font.pixelSize: fontPixelSize
    }
}
