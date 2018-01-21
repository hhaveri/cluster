import QtQuick 2.10
import QtGraphicalEffects 1.0

Item {
    id: root

    implicitWidth: 800
    implicitHeight: 600

    Component.onCompleted: {
        background.grabToImage(function(result) { result.saveToFile("gfx/full_background.png"); });
        dial.mainItem.grabToImage(function(result) { result.saveToFile("gfx/center_dial.png"); });
        foreground.mainItem.grabToImage(function(result) { result.saveToFile("gfx/center_foreground.png"); });
        foreground.handItem.grabToImage(function(result) { result.saveToFile("gfx/center_hand.png"); });
        foreground.leftItem.grabToImage(function(result) { result.saveToFile("gfx/left_indicator.png"); });
        foreground.rightItem.grabToImage(function(result) { result.saveToFile("gfx/right_indicator.png"); });
    }

    FontLoader {
        id: segmentFont

        source: "qrc:/fonts/DSEG14Classic-Regular.ttf"
    }

    ClusterLayout {
        id: background

        anchors.fill: parent

        mainContent: Item {
            anchors.fill: parent

            Item {
                anchors {
                    fill: parent
                    margins: 5
                }

                ConicalGradient {
                    anchors.fill: parent

                    gradient: Gradient {
                        GradientStop {
                            position: 0.0
                            color: "#606060"
                        }
                        GradientStop {
                            position: 0.1
                            color: "#808080"
                        }
                        GradientStop {
                            position: 0.2
                            color: "#606060"
                        }
                        GradientStop {
                            position: 0.3
                            color: "#808080"
                        }
                        GradientStop {
                            position: 0.4
                            color: "#606060"
                        }
                        GradientStop {
                            position: 0.5
                            color: "#808080"
                        }
                        GradientStop {
                            position: 0.6
                            color: "#606060"
                        }
                        GradientStop {
                            position: 0.7
                            color: "#808080"
                        }
                        GradientStop {
                            position: 0.8
                            color: "#606060"
                        }
                        GradientStop {
                            position: 0.9
                            color: "#808080"
                        }
                        GradientStop {
                            position: 1.0
                            color: "#606060"
                        }
                    }

                    Image {
                        anchors.fill: parent

                        fillMode: Image.Tile
                        opacity: 0.4
                        source: "qrc:/gfx/dial_texture.svg"
                        sourceSize: Qt.size(5, 5)
                    }

                    layer.enabled: true
                    layer.effect: RadialBlur {
                        angle: 20
                        samples: 50
                    }
                }

                Rectangle {
                    id: backgroundMainMask

                    anchors.fill: parent

                    radius: height * 0.5
                    visible: false
                }

                layer.enabled: true
                layer.effect: OpacityMask {
                    maskSource: backgroundMainMask
                }
            }

            Rectangle {
                width: parent.height * 0.4
                height: parent.height * 0.4
                anchors.centerIn: parent

                border {
                    color: "black"
                    width: height * 0.01
                }

                color: "#303030"
                radius: height * 0.5

                layer.enabled: true
                layer.effect: DropShadow {
                    samples: parent.height * 0.1
                }
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
                text: "000"

                layer.enabled: true
                layer.effect: Glow {
                    color: "#202020"
                    samples: height * 0.1
                    spread: 1
                }
            }
        }

        boardContent: Item {
            anchors.fill: parent

            Item {
                anchors {
                    fill: parent
                    margins: 5
                }

                Item {
                    id: backgroundBoardMask

                    anchors.fill: parent

                    Item {
                        anchors.fill: parent

                        Rectangle {
                            anchors {
                                fill: parent
                                topMargin: parent.height * 0.2
                                bottomMargin: parent.height * 0.2
                            }

                            radius: height * 0.2
                        }

                        Rectangle {
                            width: height
                            anchors {
                                top: parent.top
                                bottom: parent.bottom
                                horizontalCenter: parent.horizontalCenter
                            }

                            radius: height * 0.5
                        }

                        Item {
                            id: boardBgInternalMask

                            anchors.fill: parent

                            visible: false

                            Rectangle {
                                width: height
                                anchors {
                                    top: parent.top
                                    bottom: parent.bottom
                                    topMargin: parent.height * 0.015
                                    bottomMargin: parent.height * 0.015
                                    horizontalCenter: parent.horizontalCenter
                                }

                                radius: height * 0.5
                            }
                        }

                        layer.enabled: true
                        layer.effect: OpacityMask {
                            invert: true
                            maskSource: boardBgInternalMask
                        }
                    }
                }

                Rectangle {
                    anchors.fill: parent

                    gradient: Gradient {
                        GradientStop {
                            position: 0.0
                            color: "#707070"
                        }
                        GradientStop {
                            position: 0.2
                            color: "#606060"
                        }
                        GradientStop {
                            position: 0.3
                            color: "#404040"
                        }
                        GradientStop {
                            position: 0.7
                            color: "#303030"
                        }
                        GradientStop {
                            position: 0.8
                            color: "#101010"
                        }
                        GradientStop {
                            position: 1.0
                            color: "#000000"
                        }
                    }
                }

                Image {
                    anchors.fill: parent

                    fillMode: Image.Tile
                    source: "qrc:/gfx/board_texture.svg"
                    sourceSize: Qt.size(10, 10)
                }

                layer.enabled: true
                layer.effect: OpacityMask {
                    maskSource: backgroundBoardMask
                }
            }

            layer.enabled: true
            layer.effect: DropShadow {
                samples: parent.height * 0.02
            }
        }

        leftContent: Image {
            anchors.centerIn: parent

            source: "qrc:/gfx/signal_left.svg"
            sourceSize: Qt.size(50, 50)

            layer.enabled: true
            layer.effect: Glow {
                color: "#202020"
                samples: 4
                spread: 1
            }
        }

        rightContent: Image {
            anchors.centerIn: parent

            source: "qrc:/gfx/signal_right.svg"
            sourceSize: Qt.size(50, 50)

            layer.enabled: true
            layer.effect: Glow {
                color: "#202020"
                samples: 4
                spread: 1
            }
        }
    }

    ClusterLayout {
        id: dial

        anchors.fill: parent

        mainContent: Item {
            id: dialItem

            anchors.fill: parent

            readonly property int minValue: 0
            readonly property int maxValue: 180

            readonly property int step: 5
            readonly property int minorStepFactor: 2
            readonly property int majorStepFactor: 4

            readonly property real startAngle: -140
            readonly property real endAngle: 140

            Repeater {
                id: repeater

                model: 1 + stepCount

                readonly property int range: dialItem.maxValue - dialItem.minValue
                readonly property real angle: dialItem.endAngle - dialItem.startAngle

                readonly property int stepCount: range / dialItem.step
                readonly property real stepAngle: angle / stepCount

                readonly property int stepSize: range / stepCount

                Item {
                    id: tick

                    anchors {
                        fill: parent
                        margins: parent.height * 0.03
                    }

                    rotation: dialItem.startAngle + index * repeater.stepAngle

                    readonly property bool majorStep: !(index % dialItem.majorStepFactor)
                    readonly property bool minorStep: !(index % dialItem.minorStepFactor)

                    Item {
                        width: 4
                        anchors {
                            top: parent.top
                            bottom: parent.bottom
                            horizontalCenter: parent.horizontalCenter
                        }

                        Rectangle {
                            id: tickItem

                            anchors {
                                left: parent.left
                                right: parent.right
                                top: parent.top
                            }
                            height: tick.majorStep ? 20 : (tick.minorStep ? 10 : 5)

                            antialiasing: true
                            color: "#c0c0c0"
                        }

                        Text {
                            anchors {
                                horizontalCenter: tickItem.horizontalCenter
                                verticalCenter: tickItem.bottom
                                verticalCenterOffset: 20
                            }

                            color: "white"
                            font {
                                pixelSize: 20
                            }
                            rotation: -tick.rotation
                            text: tick.majorStep ? index * repeater.stepSize : ""
                        }
                    }
                }
            }

            layer.enabled: true
            layer.effect: DropShadow {
                samples: 10
            }
        }
    }

    ClusterLayout {
        id: foreground

        mainContent: Item {
            anchors.fill: parent

            Rectangle {
                id: centerRect

                width: parent.height * 0.4
                height: parent.height * 0.4
                anchors.centerIn: parent

                border {
                    color: "#6080a0"
                    width: height * 0.01
                }

                color: "#303030"
                radius: height * 0.5

                layer.enabled: true
                layer.effect: Glow {
                    color: "#406080"
                    samples: height
                }
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
                opacity: 0.2
                text: "000"

                layer.enabled: true
                layer.effect: Glow {
                    color: "#202020"
                    samples: height * 0.1
                    spread: 1
                }
            }
        }

        handContent: Item {
            anchors.fill: parent

            Image {
                height: parent.height * 0.3
                anchors {
                    left: parent.left
                    right: parent.right
                    top: parent.top
                    topMargin: parent.height * 0.1
                }

                opacity: 0.8
                source: "qrc:/gfx/dial.svg"
                sourceSize: Qt.size(width, height)

                layer.enabled: true
                layer.effect: ColorOverlay {
                    color: "red"
                }
            }

            layer.enabled: true
            layer.effect: Glow {
                color: "red"
                spread: 0.2
            }
        }

        leftContent: Item {
            anchors.fill: parent

            Image {
                anchors.centerIn: parent

                source: "qrc:/gfx/signal_left.svg"
                sourceSize: Qt.size(50, 50)

                layer.enabled: true
                layer.effect: ColorOverlay {
                    color: "#00ff00"
                }
            }

            layer.enabled: true
            layer.effect: Glow {
                color: "#00ff00"
                samples: 20
                spread: 0.2
            }
        }

        rightContent: Item {
            anchors.fill: parent

            Image {
                anchors.centerIn: parent

                source: "qrc:/gfx/signal_right.svg"
                sourceSize: Qt.size(50, 50)

                layer.enabled: true
                layer.effect: ColorOverlay {
                    color: "#00ff00"
                }
            }

            layer.enabled: true
            layer.effect: Glow {
                color: "#00ff00"
                samples: 20
                spread: 0.2
            }
        }
    }
}

