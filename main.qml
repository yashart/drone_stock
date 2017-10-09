import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        Page1 {
        }
        Page1 {
        }
    }


    footer: TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex
        TabButton {
            text: qsTr("Стенка")
            onClicked: {
                worldInterface.read_drone_info("top_by_top.txt");
                worldInterface.make_one_step();
            }
        }
        TabButton {
            text: qsTr("Уголки")
            onClicked: {
                worldInterface.read_drone_info("corners.txt");
                worldInterface.make_one_step();
            }
        }
    }
}
