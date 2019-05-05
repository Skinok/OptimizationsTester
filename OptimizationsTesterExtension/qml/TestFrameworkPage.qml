import QtQuick 2.12
import QtQuick.Controls 2.12


/*
 *
  This page will give the user the opportunity to compare different optimizations in code samples.
  It will show the results of optimizations and hints the user on the best suited for his case
 */
Item {
    id: helpOptimizationPage

    // Item API

    //Background
    Rectangle {
        id: background
        anchors.fill: parent
        color: "#5f5f5f"

        Label {
            id: label
            x: 18
            y: 15
            width: 228
            height: 13
            color: "#ffffff"
            text: qsTr("Welcome in the optimization test plugin !")
            styleColor: "#ffffff"
        }

        Button {
            id: button
            x: 241
            y: 44
            text: qsTr("Install Optimization Runner")
            onClicked: {
                OptimManager.initializeOptimRunner()
            }
        }
    }

    //**
    // Text editors and result row below
    //**
    Image {
        id: image
        x: 22
        y: 113
        width: 217
        height: 205
        sourceSize.height: 400
        sourceSize.width: 400
        fillMode: Image.PreserveAspectFit
        source: "images/OptimRunnerTree.png"
    }

    //**
    // Footer
    //**


    /*
    Row{


    }
    */
}

/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:3;anchors_x:241;anchors_y:44}
}
 ##^##*/

