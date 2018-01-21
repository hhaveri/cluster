import QtQuick 2.10

Item {
    id: root

    implicitWidth: 800
    implicitHeight: 600

    readonly property alias boardItem: boardItem
    readonly property alias handItem: handItem
    readonly property alias leftItem: leftItem
    readonly property alias mainItem: mainItem
    readonly property alias rightItem: rightItem

    property alias boardContent: boardItem.data
    property alias handContent: handItem.data
    property alias leftContent: leftItem.data
    property alias mainContent: mainItem.data
    property alias rightContent: rightItem.data

    Item {
        id: handItem

        width: height * 0.03
        anchors {
            top: parent.top
            bottom: parent.bottom
            horizontalCenter: parent.horizontalCenter
        }
    }

    Item {
        id: mainItem

        width: height
        anchors {
            top: parent.top
            bottom: parent.bottom
            horizontalCenter: parent.horizontalCenter
        }
    }

    Item {
        id: boardItem

        anchors.fill: parent
    }

    Item {
        height: width
        anchors {
            left: parent.left
            right: mainItem.left
            verticalCenter: parent.verticalCenter
        }

        Item {
            id: leftItem

            width: 100
            height: 100

            anchors.centerIn: parent
        }
    }

    Item {
        height: width
        anchors {
            left: mainItem.right
            right: parent.right
            verticalCenter: parent.verticalCenter
        }

        Item {
            id: rightItem

            width: 100
            height: 100

            anchors.centerIn: parent
        }
    }
}

