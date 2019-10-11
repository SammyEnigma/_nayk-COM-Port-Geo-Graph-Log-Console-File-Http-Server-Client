import QtQuick 2.13
import QtQuick.Controls 2.12
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.12
import "Theme.js" as Theme;

MenuItem {
    id: menuItem
    implicitWidth: Theme.menuWidth
    implicitHeight: Theme.fontPixelSize * 2 + 6

    contentItem: Text {
        leftPadding: menuItem.implicitHeight
        rightPadding: menuItem.implicitHeight
        text: menuItem.text
        font: menuItem.font
        opacity: enabled ? 1.0 : 0.3
        color: menuItem.highlighted ? Theme.textColorLight : Theme.textColor
        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
    }

    background: Rectangle {
        anchors.fill: parent
        anchors.margins: 4
        color: menuItem.highlighted ? Theme.menuHighlight : "transparent"
        radius: Theme.buttonRadius - 2
    }
}
