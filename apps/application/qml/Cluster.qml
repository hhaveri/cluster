import QtQuick 2.10

ClusterLayout {
    id: root

    FontLoader {
        id: segmentFont

        source: "qrc:/fonts/DSEG14Classic-Regular.ttf"
    }

    Timer {
        id: signalTimer

        interval: 500
        repeat: true
        running: application.telemetry.leftSignal || application.telemetry.rightSignal
        triggeredOnStart: !on

        property bool on: false

        onTriggered: on = !on
    }

    centerContent: Item {
        anchors.fill: parent

        Image {
            id: dial

            anchors.centerIn: parent

            source: "qrc:/gfx/center_dial.png"
        }

        Image {
            anchors.centerIn: parent

            rotation: startAngle + application.telemetry.cappedSpeed * stepAngle
            source: "qrc:/gfx/center_hand.png"

            readonly property real startAngle: -140
            readonly property real endAngle: 140

            readonly property real stepAngle: (endAngle - startAngle) / application.telemetry.maxSpeed

            Behavior on rotation {
                SmoothedAnimation {
                    duration: 500
                    velocity: -1
                }
            }
        }

        Image {
            anchors.centerIn: parent

            source: "qrc:/gfx/center_foreground.png"
        }

        Text {
            width: parent.height * 0.3
            height: parent.height * 0.12
            anchors.centerIn: parent

            horizontalAlignment: Text.AlignRight

            font {
                family: segmentFont.name
                pixelSize: height
            }
            color: "#406080"
            text: application.telemetry.cappedSpeed
        }
    }

    leftContent: Image {
        anchors.centerIn: parent

        source: "qrc:/gfx/left_indicator.png"
        visible: application.telemetry.leftSignal && signalTimer.on
    }

    rightContent:Image {
        anchors.centerIn: parent

        source: "qrc:/gfx/right_indicator.png"
        visible: application.telemetry.rightSignal && signalTimer.on
    }

    states: State {
        when: !root.enabled

        PropertyChanges {
            target: root

            opacity: 0
        }

        PropertyChanges {
            target: dial

            scale: 0.8
        }
    }

    transitions: [
        Transition {
            ParallelAnimation {
                OpacityAnimator {
                    duration: 500
                    easing.type: Easing.OutQuad
                }

                ScaleAnimator {
                    duration: 500
                    easing.type: Easing.OutQuad
                }
            }
        }
    ]
}

