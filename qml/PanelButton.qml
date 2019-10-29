import QtQuick 2.13
import QtQuick.Controls 2.12
import "Style.js" as Style

ToolButton {
    id: root
    font.pointSize: Style.fontPointSize
    implicitHeight: Style.buttonHeight
    implicitWidth: Style.buttonHeight
    opacity: enabled ? 1.0 : Style.disabledControlOpacity
    property string iconSource: ""

    contentItem: Item {
        anchors.fill: parent

        Image {
            id: _img
            source: root.iconSource
            visible: root.iconSource !== ""
            anchors.centerIn: parent
            width: Math.min( parent.width, parent.height )
            height: width
            fillMode: Image.Stretch
            horizontalAlignment: Image.AlignHCenter
            verticalAlignment: Image.AlignVCenter
        }

        Text {
            id: _text
            anchors.centerIn: parent
            visible: !_img.visible
            text: root.text
            font: root.font
            color: root.hovered ? (root.down ? Style.highlightColor : Style.textLightColor) : Style.textColor
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
    }

    background: Rectangle {
        anchors.fill: parent
        color: root.hovered ? (root.down ? Style.bgDarkColor : Style.menuHighlightColor) : Style.bgLightColor
        border.color: Style.menuHighlightColor
        border.width: Style.buttonBorder
        radius: Style.buttonRadius - 3
    }
}
