import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.12
import "Theme.js" as Theme;

Button {
    id: button
    text: qsTr("Button")
    font.pixelSize: Theme.fontPixelSize
    opacity: enabled ? 1.0 : 0.3

    contentItem: Text {
        text: button.text
        font: button.font
        color: button.down ? Theme.colorHighlight : Theme.textColorLight
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
    }

    background: Rectangle {
        implicitWidth: 100
        implicitHeight: Theme.fontPixelSize * 2 + 6
        color: button.hovered ? (button.down ? Theme.bgColorDark : Theme.menuHighlight) : Theme.bgColorLight
        border.color: button.down ? Theme.colorHighlight : Theme.borderColor
        border.width: Theme.borderWidth
        radius: Theme.buttonRadius
    }
}
