import QtQuick 2.12
import QtQuick.Controls 2.12

Item {
    id: rootGraphicNumber
    width: 40
    height: 40

    property alias numberString: textNumber.text
    property string backgroundColor: "transparent"
    property string textColor: "green"
    property string borderColor: "green"
    property alias fontSize: textNumber.font.pixelSize
    property alias numberLabel: label.text

    Rectangle {
        id: background

        width: 40
        height: 40

        border.width: 2

        radius: width * 0.5
        border.color: "#5ef366"
        color: "transparent"

        Text {
            id: textNumber
            color: "#5ef366"

            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter

            text: "1"

            font.bold: false
            font.pixelSize: 26
        }
    }

    Label {
        id: label
        width: 117
        height: 26

        anchors.verticalCenter: background.verticalCenter
        anchors.left: background.right
        anchors.leftMargin: 10

        color: "#5ef366"
        text: qsTr("Add Project")

        font.bold: false
        font.pointSize: 16
    }
}




/*##^## Designer {
    D{i:3;anchors_width:117;anchors_x:46}
}
 ##^##*/
