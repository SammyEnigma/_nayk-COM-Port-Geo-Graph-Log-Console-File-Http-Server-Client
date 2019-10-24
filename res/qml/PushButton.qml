import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.12
import "Theme.js" as Theme;

Button {
    id: root
    text: qsTr("Button")
    font.pointSize: Theme.fontPointSize
    opacity: enabled ? 1.0 : 0.3

    contentItem: Text {
        text: root.text
        font: root.font
        color: root.down ? Theme.colorHighlight : Theme.textColorLight
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
    }

    background: Rectangle {
        implicitWidth: 100
        implicitHeight: Theme.itemHeight
        color: root.hovered ? (root.down ? Theme.bgColorDark : Theme.menuHighlight) : Theme.bgColorLight
        border.color: root.down ? Theme.colorHighlight : Theme.borderColor
        border.width: Theme.borderWidth
        radius: Theme.buttonRadius
    }
}
