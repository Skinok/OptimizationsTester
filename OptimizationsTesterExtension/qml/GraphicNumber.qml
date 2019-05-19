import QtQuick 2.0

Item {

    property alias numberString: textNumber.text
    property alias backgroundColor: background.color
    property alias borderColor: background.border.color
    property alias fontSize: textNumber.font.pixelSize

    Rectangle {
        id: background

        width: 40
        height: 40

        color: "white"
        border.color: "green"
        border.width: 3

        radius: width * 0.5

        Text {
            id: textNumber

            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter

            color: background.border.color
            text: "1"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.bold: true
            font.pixelSize: 26
        }
    }
}

/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/

