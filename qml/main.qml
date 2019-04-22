import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12



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

    StackLayout {
        id: stackView
        height: parent.height - tabBar.height
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.top: tabBar.bottom
        anchors.topMargin: 0

        currentIndex: tabBar.currentIndex

        // Page 1
        LiveCodeOptimizationPage{
            id:liveCodePages
            height: window.height
            width: window.width
        }

        // Page 2
        // OptimizationExamplesPage{ }
        Rectangle{
            id: test2

            color: "grey"
        }
    }
}

































/*##^## Designer {
    D{i:1;anchors_width:298;anchors_x:7;anchors_y:70}
}
 ##^##*/
