import QtQuick 2.10
import QtQuick.Window 2.10

Window {
    width: 400
    height: 200

    //: Application title
    //% "Cluster Simulator"
    title: qsTrId("title")
    visible: true

    Item {
        anchors.fill: parent

        focus: true

        Keys.onUpPressed: {
            if (simulator.telemetry.speed < 200) {
                simulator.telemetry.speed += 1;
            }
        }
        Keys.onDownPressed: {
            if (simulator.telemetry.speed > 0) {
                simulator.telemetry.speed -= 1;
            }
        }
        Keys.onLeftPressed: simulator.telemetry.leftSignal = !simulator.telemetry.leftSignal
        Keys.onRightPressed: simulator.telemetry.rightSignal = !simulator.telemetry.rightSignal

        Text {
            anchors.centerIn: parent
            anchors.horizontalCenterOffset: -50

            text: simulator.telemetry.leftSignal ? "<-" : ""
        }

        Text {
            anchors.centerIn: parent

            text: simulator.telemetry.speed
        }

        Text {
            anchors.centerIn: parent
            anchors.horizontalCenterOffset: 50

            text: simulator.telemetry.rightSignal ? "->" : ""
        }
    }
}
