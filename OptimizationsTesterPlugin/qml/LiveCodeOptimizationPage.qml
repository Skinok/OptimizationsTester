import QtQuick 2.12
import QtQuick.Controls 2.12

/*
 *
  This page will give the user the opportunity to compare different optimizations in code samples.
  It will show the results of optimizations and hints the user on the best suited for his case
 */
Item{
    id: liveCodeOptimizationPage

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
    Row{
        id: editorsRow

        width: parent.width
        height: parent.height - 150

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top : parent.top

        topPadding: 2.0
        leftPadding: 2.0
        rightPadding: 2.0

        spacing: 4

        // First Text area
        Item{
            id: leftTextEditor

            width: ( parent.width -parent.spacing - parent.leftPadding - parent.rightPadding) / 2.0;
            height: parent.height;

            Text{
                id: beforeOptimsLabel
                width: contentWidth
                height: 30

                anchors.top: parent.top
                anchors.bottom: leftEditor.top

                text: "Copy/paste below the code to optimize"
            }

            TextArea{
                id: leftEditor

                width: parent.width
                height: parent.height - leftEditorResults.height

                anchors.top: parent.top
                anchors.left: parent.left
                anchors.right: parent.right

                background: Rectangle{
                    color: "white"
                }

                text: DataModel.skeletonBefore
            }

            Item{
                id: leftEditorResults

                height: 50
                width: parent.width

                anchors.top: leftEditor.bottom
                anchors.topMargin: 2

                Text{
                    id: leftPerformance
                    width: contentWidth
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: "Performance : "
                }
            }
        }

        // Second Text area
        Item{
            id: rightTextEditor

            width: ( parent.width -parent.spacing - parent.leftPadding - parent.rightPadding) / 2.0;
            height: parent.height;

            Text{
                id: afterOptimsLabel
                width: contentWidth
                height: 30

                anchors.top: parent.top
                anchors.bottom: rightEditor.top

                text: "Code below the optimizations to bring"
            }

            TextArea{
                id: rightEditor

                width: parent.width
                height: parent.height - rightEditorResults.height

                anchors.top: parent.top
                anchors.left: parent.left
                anchors.right: parent.right

                background: Rectangle{
                    color: "white"
                }

                text: DataModel.skeletonAfter
            }

            Item{
                id: rightEditorResults
                height: 50
                width: parent.width

                anchors.top: rightEditor.bottom
                anchors.topMargin: 2

                Text{
                    id: rightPerformance
                    width: contentWidth
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: "Performance : "
                }
            }
        }
    }

    //**
    // Central "Go" Button
    //**
    Item{
        id: buttonRow
        height:210
        width:parent.width

        anchors.top : editorsRow.bottom

        // Comparison button
        Button {
            id: comparisonButton

            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin: 4
            anchors.rightMargin: 2

            text: qsTr("Compare")
            width: 200
            height: 50

            font.pixelSize: 16

            contentItem: Text {
                text: comparisonButton.text
                font: comparisonButton.font
                opacity: enabled ? 1.0 : 0.3
                color: comparisonButton.down ? "#17a81a" : "#21be2b"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
            }

            background: Rectangle {
                implicitWidth: 100
                implicitHeight: 40
                opacity: enabled ? 1 : 0.3
                border.color: comparisonButton.down ? "#17a81a" : "#21be2b"
                border.width: 1
                radius: 2
            }

            onClicked: {
                console.log("Go Compare!")
                PerformanceMgr.compareLiveCoding( leftEditor.text, rightEditor.text );
            }
        }

    }

    //**
    // Footer
    //**
    /*Row{


    }
    */

}

/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
