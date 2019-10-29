import QtQuick 2.13
import QtQuick.Controls 2.12
import "Style.js" as Style

TextField {
    id: root
    implicitWidth: Style.itemWidth
    implicitHeight: Style.itemHeight
    font.pointSize: Style.fontPointSize
    text: ""
    padding: Style.minPadding
    horizontalAlignment: Qt.AlignLeft
    verticalAlignment: Qt.AlignVCenter
    opacity: enabled ? 1.0 : Style.disabledControlOpacity
    color: Style.textColor
    placeholderTextColor: Style.bgLightColor
    selectionColor: Style.menuHighlightColor
    selectedTextColor: Style.textLightColor

    background: Rectangle {
        anchors.fill: parent
        color: Style.bgDarkColor
        border.color: Style.borderColor
        border.width: Style.editorBorder
        radius: Math.max(0, Style.buttonRadius - 2)
    }
}
