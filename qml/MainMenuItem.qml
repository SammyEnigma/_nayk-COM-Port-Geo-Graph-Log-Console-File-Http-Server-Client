import QtQuick 2.13
import QtQuick.Controls 2.12
import "Style.js" as Style

MenuItem {
    id: root
    implicitWidth: Style.itemWidth
    implicitHeight: Style.itemHeight
    opacity: enabled ? 1.0 : Style.disabledControlOpacity
    property string iconSource: ""

    background: Rectangle {
        anchors.fill: parent
        anchors.margins: Style.minPadding
        color: root.highlighted ? Style.menuHighlightColor : "transparent"
        radius: Style.buttonRadius - 2
    }

    contentItem: Item {
        anchors.fill: parent

        Image {
            id: _img
            horizontalAlignment: Image.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            source: root.iconSource
            height: root.height - 8
            width: height
            visible: root.iconSource !== ""
            fillMode: Image.Stretch
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 8
        }

        Text {
            id: _text
            text: root.text
            font: root.font
            color: root.highlighted ? Style.textLightColor : Style.textColor
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
            elide: Text.ElideRight
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: _img.right
            anchors.leftMargin: 8
        }
    }
}
