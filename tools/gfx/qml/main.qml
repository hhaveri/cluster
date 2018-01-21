import QtQuick 2.10
import QtQuick.Window 2.10

Window {
    width: 800
    height: 600

    //: Application title
    //% "Gfx Tool"
    title: qsTrId("title")

    visible: true

    Cluster {
        id: cluster

        anchors.centerIn: parent
    }
}
