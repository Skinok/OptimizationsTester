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
            x: 34
            y: 84
            width: 956
            height: 66
            color: "#ffffff"
            text: qsTr("You are here to test two code samples and easily compare their respective execution time.\nWhich one is the fastest one ? Let's find out together !")
            anchors.verticalCenterOffset: -280
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
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
            anchors.horizontalCenterOffset: -360
            anchors.verticalCenterOffset: -240
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            font.bold: false
            font.pointSize: 16
        }

        Text {
            id: element1
            x: 54
            y: 178
            width: 956
            height: 66
            color: "#ffffff"
            text: qsTr("This plugin will install in this instance of Qt Creator a very light and fully customizable framework that will help you to quickly test your code samples.\nFollow the steps and you will be able to hack some c++ in a few seconds")
            anchors.verticalCenterOffset: -180
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            wrapMode: Text.WordWrap
            elide: Text.ElideNone
            textFormat: Text.AutoText
            font.pixelSize: 14
            renderType: Text.QtRendering
            fontSizeMode: Text.FixedSize
        }

        Text {
            id: element2
            x: 42
            y: 374
            width: 321
            height: 48
            color: "#ffffff"
            text: qsTr("Click on the above button and install the small project in your Qt Creator session")
            anchors.verticalCenterOffset: 20
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenterOffset: -260
            anchors.horizontalCenter: parent.horizontalCenter
            wrapMode: Text.WordWrap
            textFormat: Text.AutoText
            renderType: Text.QtRendering
            elide: Text.ElideNone
            font.pixelSize: 14
            fontSizeMode: Text.FixedSize
        }

        GraphicNumber {
            id: graphicNumber2
            x: 54
            y: 250
            width: 40
            height: 40
            anchors.verticalCenterOffset: -110
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenterOffset: -450
            anchors.horizontalCenter: parent.horizontalCenter
            textColor: "#5ef366"
            numberString: "1"
            borderColor: "#5ef366"
            fontSize: 23
            backgroundColor: "transparent"
        }

        Text {
            id: element3
            x: 8
            y: 558
            width: 492
            height: 47
            color: "#ffffff"
            text: qsTr("Put your code before optimization inside : \n userwrittenclassbefore.hpp Put your code after optimizations inside : \n userwrittenclassafter.hpp ")
            anchors.verticalCenterOffset: 200
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenterOffset: -200
            anchors.horizontalCenter: parent.horizontalCenter
            font.pixelSize: 14
            fontSizeMode: Text.HorizontalFit
            wrapMode: Text.WordWrap
            elide: Text.ElideNone
            textFormat: Text.RichText
            renderType: Text.QtRendering
        }

        Text {
            id: element5
            x: 740
            y: 360
            width: 250
            height: 48
            color: "#ffffff"
            text: qsTr("Look in the Edit tab and find the OptimRunner project")
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenterOffset: 360
            anchors.horizontalCenter: parent.horizontalCenter
            font.pixelSize: 14
            fontSizeMode: Text.FixedSize
            wrapMode: Text.WordWrap
            elide: Text.ElideNone
            textFormat: Text.AutoText
            renderType: Text.QtRendering
        }

        GraphicNumber {
            id: graphicNumber6
            x: 630
            y: 542
            width: 40
            height: 40
            anchors.verticalCenterOffset: 180
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenterOffset: 100
            anchors.horizontalCenter: parent.horizontalCenter
            numberLabel: "Launch and check results"
            textColor: "#5ef366"
            numberString: "4"
            borderColor: "#5ef366"
            fontSize: 23
            backgroundColor: "transparent"
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
        anchors.verticalCenterOffset: -350
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
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

        y: 311
        width: 228
        height: 46
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.horizontalCenterOffset: -275

        text: qsTr("Install Optimization Runner")
        anchors.verticalCenterOffset: -50
        anchors.verticalCenter: parent.verticalCenter
        font.pixelSize: 16
        font.kerning: false
        font.preferShaping: true
        focusPolicy: Qt.WheelFocus
        checkable: true
        checked: OptimManager.optimRunnerInstalled

        contentItem: Text {
            text: initButton.text
            font: initButton.font
            opacity: enabled ? 1.0 : 0.3
            color: initButton.down ? "#17a81a" : "#21be2b"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        background: Rectangle {
            implicitWidth: 100
            implicitHeight: 40
            opacity: enabled ? 1 : 0.3
            border.color: initButton.down ? "#17a81a" : "#21be2b"
            border.width: 1
            radius: 2
        }

        onClicked: {
            OptimManager.initializeOptimRunner()
        }
    }

    Image {
        id: imageOptimRunnerTree
        x: 497
        y: 282
        width: 217
        height: 205
        anchors.verticalCenterOffset: 10
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenterOffset: 100
        anchors.horizontalCenter: parent.horizontalCenter
        sourceSize.height: 400
        sourceSize.width: 400
        fillMode: Image.PreserveAspectFit
        source: "images/OptimRunnerTree.png"
    }

    GraphicNumber {
        id: graphicNumber1
        x: 428
        y: 241
        width: 40
        height: 40
        anchors.verticalCenterOffset: -130
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenterOffset: -30
        anchors.horizontalCenter: parent.horizontalCenter
        numberLabel: "Find the source code"
        textColor: "#5ef366"
        numberString: "2"
        backgroundColor: "transparent"
        borderColor: "#5ef366"
        fontSize: 23
    }

    GraphicNumber {
        id: graphicNumber3
        x: 30
        y: 505
        width: 40
        height: 40
        anchors.verticalCenterOffset: 130
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenterOffset: -450
        anchors.horizontalCenter: parent.horizontalCenter
        numberLabel: "Write your code !"
        textColor: "#5ef366"
        numberString: "3"
        borderColor: "#5ef366"
        fontSize: 23
        backgroundColor: "transparent"
    }

    Image {
        id: imageOptimRunnerTree1
        x: 38
        y: 613
        width: 403
        height: 147
        anchors.verticalCenterOffset: 290
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenterOffset: -220
        anchors.horizontalCenter: parent.horizontalCenter
        sourceSize.width: 400
        fillMode: Image.PreserveAspectFit
        source: "images/OptimRunner_user_before_class.png"
        sourceSize.height: 400
    }

    Image {
        id: imageOptimRunnerTree2
        x: 655
        y: 649
        width: 346
        height: 47
        anchors.verticalCenterOffset: 280
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenterOffset: 300
        anchors.horizontalCenter: parent.horizontalCenter
        sourceSize.width: 400
        fillMode: Image.PreserveAspectFit
        source: "images/Results.png"
        sourceSize.height: 400
    }

    Text {
        id: element6
        x: 639
        y: 595
        width: 346
        height: 48
        color: "#ffffff"
        text: qsTr("Verify your optimizations, and optimize again if needed")
        anchors.verticalCenterOffset: 230
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenterOffset: 300
        anchors.horizontalCenter: parent.horizontalCenter
        elide: Text.ElideNone
        font.pixelSize: 14
        wrapMode: Text.WordWrap
        fontSizeMode: Text.FixedSize
        textFormat: Text.AutoText
        renderType: Text.QtRendering
    }
}




/*##^## Designer {
    D{i:2;anchors_x:34;anchors_y:84}D{i:3;anchors_x:34;anchors_y:146}D{i:4;anchors_x:54;anchors_y:178}
D{i:5;anchors_x:42;anchors_y:375}D{i:6;anchors_x:54;anchors_y:250}D{i:7;anchors_height:26;anchors_width:117;anchors_x:416;anchors_y:239}
D{i:10;anchors_height:26;anchors_width:117;anchors_x:416;anchors_y:239}D{i:12;anchors_x:241;anchors_y:44}
D{i:11;anchors_x:241;anchors_y:44}D{i:14;anchors_x:497;anchors_y:282}D{i:15;anchors_x:428;anchors_y:241}
D{i:16;anchors_x:30;anchors_y:505}D{i:17;anchors_x:38;anchors_y:613}D{i:18;anchors_x:655;anchors_y:578}
}
 ##^##*/
