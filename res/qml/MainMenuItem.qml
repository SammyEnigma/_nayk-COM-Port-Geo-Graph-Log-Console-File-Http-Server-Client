import QtQuick 2.13
import QtQuick.Controls 2.12
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.12
import "Theme.js" as Theme;

MenuItem {
    id: _menuItem
    implicitWidth: Theme.menuWidth
    implicitHeight: Theme.itemHeight

    contentItem: Text {
        leftPadding: _menuItem.implicitHeight
        rightPadding: _menuItem.implicitHeight
        text: _menuItem.text
        font: _menuItem.font
        opacity: enabled ? 1.0 : 0.3
        color: _menuItem.highlighted ? Theme.textColorLight : Theme.textColor
        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
    }

    background: Rectangle {
        anchors.fill: parent
        anchors.margins: 4
        color: _menuItem.highlighted ? Theme.menuHighlight : "transparent"
        radius: Theme.buttonRadius - 2
    }
}
