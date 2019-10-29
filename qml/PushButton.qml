import QtQuick 2.0
import QtQuick.Controls 2.12
import "Style.js" as Style

Button {
    id: root
    implicitWidth: Style.buttonWidth
    implicitHeight: Style.buttonHeight
    text: "Button"
    font.pointSize: Style.fontPointSize
    font.bold: hovered
    opacity: enabled ? 1.0 : Style.disabledControlOpacity
    property string iconSource: ""

    contentItem: Item {
        anchors.fill: parent

        Image {
            id: _img
            height: parent.height - 8
            width: height
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: (parent.width - width - _text.contentWidth) / 2
            source: root.iconSource
            visible: root.iconSource !== ""
            fillMode: Image.Stretch
            horizontalAlignment: Image.AlignHCenter
            verticalAlignment: Image.AlignVCenter
        }

        Text {
            id: _text
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: _img.visible ? _img.right : parent.left
            anchors.leftMargin: _img.visible ? 0 : (parent.width - contentWidth) / 2
            text: root.text
            font: root.font
            color: root.hovered ? (root.down ? Style.highlightColor : Style.textLightColor) : Style.textColor
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
    }

    background: Rectangle {
        id: _bg
        anchors.fill: parent
        color: root.hovered ? (root.down ? Style.bgDarkColor : Style.menuHighlightColor) : Style.bgLightColor
        border.color: root.down ? Style.highlightColor : Style.borderColor
        border.width: Style.buttonBorder
        radius: Style.buttonRadius
    }
}
