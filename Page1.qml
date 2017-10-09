import QtQuick 2.7
import QtQuick.Layouts 1.3


Item {
    property alias topByTopGrid: topByTopGrid
    GridLayout {
        id: topByTopGrid
        anchors.fill: parent
        columns: 100
        rows: 100
        rowSpacing: 0
        columnSpacing: 0
        anchors.margins: 0
        Repeater {
            id: gridData
            model: 100*100
            delegate: Rectangle {
                color: (worldInterface.get_map_point(parseInt(index / 100), parseInt(index % 100)) == 0)?
                           "green" : worldInterface.get_color(
                              worldInterface.get_map_point(parseInt(index / 100), parseInt(index % 100)))
                //color: "green"
                border.color: "black"
                Layout.fillWidth: true
                Layout.fillHeight: true
                Timer {
                    interval: 100; running: true; repeat: true
                    onTriggered: {
                        parent.color = (worldInterface.get_map_point(parseInt(index / 100), parseInt(index % 100)) == 0)?
                                    "green" : worldInterface.get_color(
                                         worldInterface.get_map_point(parseInt(index / 100), parseInt(index % 100)))
                    }
                }
            }
        }

        function init_grid (file) {
            worldInterface.read_drone_info(file)
        }
        function one_step () {
            worldInterface.make_one_step()
            //worldInterface.dump()
        }
    }
    Timer {
        interval: 500; running: true; repeat: true
        onTriggered: {
            console.log("tick")
            topByTopGrid.one_step()
        }
    }
    Component.onCompleted: {
        //console.log("tick tack")
        //topByTopGrid.init_grid("top_by_top.txt")

        //topByTopGrid.visible = false
        //topByTopGrid.visible = true
    }
}
