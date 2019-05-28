import QtQuick 2.12
import QtQuick.Window 2.2
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12
import QtQuickDesignerTheme 1.0

Item {
    id: window

    width: 1280
    height: 800

    antialiasing: true

    // property API here
    TabBar {
        id: tabBar
        width: parent.width
        height: 50
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.topMargin: 0

        TabButton {
            text: "Quick optimization test"
        }

        TabButton {
            text: "Optimization examples"
        }
    }

    StackLayout {
        id: mainStackedLayout
        anchors.top: tabBar.bottom

        width: parent.width
        height: parent.height - tabBar.height

        currentIndex: tabBar.currentIndex

        TestFrameworkPage {
            id: testFrameworkPage
        }

        OptimizationsExamplesPage {
            id: examplePage
        }
    }
}

/*##^## Designer {
    D{i:1;anchors_width:298;anchors_x:7;anchors_y:70}
}
 ##^##*/

