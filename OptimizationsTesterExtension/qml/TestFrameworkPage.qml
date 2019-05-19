import QtQuick 2.12
import QtQuick.Controls 2.12


/*
 *
  This page will give the user the opportunity to compare different optimizations in code samples.
  It will show the results of optimizations and hints the user on the best suited for his case
 */
Item {
    id: helpOptimizationPage
    width: 1024
    height: 768

    // Item API

    //Background
    Rectangle {
        id: background
        width: 1024
        height: 768
        anchors.fill: parent
        color: "#5f5f5f"
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0

        Text {
            id: element
            x: 67
            y: 82
            width: 890
            height: 66
            color: "#ffffff"
            text: qsTr("You are here to test two code samples and easily compare their respective execution time.\nWhich one is the fastest one ? Let's find out together !")
            fontSizeMode: Text.FixedSize
            renderType: Text.QtRendering
            font.pixelSize: 16
        }

        Label {
            id: label
            x: 34
            y: 146
            width: 237
            height: 26
            color: "#5ef366"
            text: qsTr("How does it work ?")
            font.pointSize: 16
        }

        Text {
            id: element1
            x: 54
            y: 178
            width: 491
            height: 66
            color: "#ffffff"
            text: qsTr("This plugin will install in this instance of Qt Creator a very light and fully customizable framework that will help you to quickly test your code samples.\nFollow the steps and you will be able to hack some c++ in a few seconds.")
            wrapMode: Text.WordWrap
            elide: Text.ElideNone
            textFormat: Text.AutoText
            font.pixelSize: 16
            renderType: Text.QtRendering
            fontSizeMode: Text.HorizontalFit
        }
    }

    Label {
        id: title
        x: 0
        y: 15
        width: parent.width
        height: 42
        color: "#ffffff"
        text: qsTr("Welcome in the Optimization Tester !")
        font.capitalization: Font.MixedCase
        font.pointSize: 26
        font.bold: false
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        fontSizeMode: Text.HorizontalFit
        renderType: Text.NativeRendering
        styleColor: "#ffffff"
    }

    Button {
        id: initButton

        y: 347
        anchors.horizontalCenter: parent.horizontalCenter

        text: qsTr("Install Optimization Runner")
        focusPolicy: Qt.WheelFocus
        anchors.horizontalCenterOffset: -327
        onClicked: {
            OptimManager.initializeOptimRunner()
        }

        //color: "#5ef366"
    }

    Image {
        id: imageOptimRunnerTree
        x: 409
        y: 264
        width: 217
        height: 205
        sourceSize.height: 400
        sourceSize.width: 400
        fillMode: Image.PreserveAspectFit
        source: "images/OptimRunnerTree.png"
    }
}

/*##^## Designer {
    D{i:6;anchors_x:241;anchors_y:44}
}
 ##^##*/

