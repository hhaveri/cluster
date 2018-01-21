import QtQuick 2.10

Item {
    implicitWidth: 800
    implicitHeight: 600

    property alias centerContent: centerItem.data
    property alias leftContent: leftItem.data
    property alias rightContent: rightItem.data

    Item {
        id: leftItem

        height: width
        anchors {
            left: parent.left
            right: centerItem.left
            verticalCenter: parent.verticalCenter
        }
    }

    Item {
        id: centerItem

        width: height
        anchors {
            top: parent.top
            bottom: parent.bottom
            horizontalCenter: parent.horizontalCenter
        }
    }

    Item {
        id: rightItem

        height: width
        anchors {
            left: centerItem.right
            right: parent.right
            verticalCenter: parent.verticalCenter
        }
    }
}

