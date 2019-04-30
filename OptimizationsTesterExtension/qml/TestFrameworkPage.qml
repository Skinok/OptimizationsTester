import QtQuick 2.12
import QtQuick.Controls 2.12

/*
 *
  This page will give the user the opportunity to compare different optimizations in code samples.
  It will show the results of optimizations and hints the user on the best suited for his case
 */
Item{
    id: helpOptimizationPage

    // Item API

    //Background
    Rectangle{
        id:background
        anchors.fill:parent
        color: "darkgrey"
    }

    //**
    // Text editors and result row below
    //**
    Image {
        id: image
        x: 209
        y: 267
        width: 380
        height: 327
        fillMode: Image.PreserveAspectFit
        source: "qrc:///images/OptimRunnerTree.png"
    }

    Rectangle {
        id: rectangle
        x: 248
        y: 93
        width: 200
        height: 200
        //color: Theme.BackgroundColorDark
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
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
