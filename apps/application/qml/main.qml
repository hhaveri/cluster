import QtQuick 2.10
import QtQuick.Window 2.10

Window {
    width: 800
    height: 600

    //: Application title
    //% "Cluster"
    title: qsTrId("title")

    visible: true

    Image {
        source: "qrc:/gfx/full_background.png"

        Loader {
            anchors.fill: parent

            asynchronous: true
            enabled: status == Loader.Ready
            source: "Cluster.qml"
            visible: enabled
        }
    }
}
