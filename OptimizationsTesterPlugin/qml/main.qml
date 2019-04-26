import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12
import QtQuickDesignerTheme 1.0

Item {
    id: window
    width: 1280
    height: 800

    TabBar {
        id: tabBar
        width: parent.width
        height: 50
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.topMargin: 0

        TabButton {
            text: "Live code optimization"
        }

        TabButton {
            text: "Optimization examples"
        }
    }

    Image {
        id: image
        x: 209
        y: 267
        width: 380
        height: 327
        fillMode: Image.PreserveAspectFit
        source: "../src/images/2019-04-25_13-48-04.png"
    }

    Rectangle {
        id: rectangle
        x: 248
        y: 93
        width: 200
        height: 200
        color: Theme.BackgroundColorDark
    }
}





































/*##^## Designer {
    D{i:1;anchors_width:298;anchors_x:7;anchors_y:70}
}
 ##^##*/
