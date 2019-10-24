import QtQuick 2.13
import QtQuick.Controls 2.12
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.12
import "Theme.js" as Theme;

TextField {
    id: _textField
    font.pointSize: Theme.fontPointSize
    text: ""
    padding: 5
    horizontalAlignment: Qt.AlignLeft
    verticalAlignment: Qt.AlignVCenter
    implicitWidth: 200
    implicitHeight: Theme.itemHeight
    opacity: enabled ? 1.0 : 0.3
    color: Theme.textColor
    placeholderTextColor: Theme.bgColorLight
    selectionColor: Theme.menuHighlight
    selectedTextColor: Theme.textColorLight

    background: Rectangle {
        anchors.fill: parent
        color: Theme.bgColorDark
        border.color: Theme.borderColor
        radius: Theme.buttonRadius - 2
    }
}
