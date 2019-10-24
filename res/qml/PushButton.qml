import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.12
import "Theme.js" as Theme;

Button {
    id: _button
    text: qsTr("Button")
    font.pointSize: Theme.fontPointSize
    opacity: enabled ? 1.0 : 0.3

    contentItem: Text {
        text: _button.text
        font: _button.font
        color: _button.down ? Theme.colorHighlight : Theme.textColorLight
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
    }

    background: Rectangle {
        implicitWidth: 100
        implicitHeight: Theme.itemHeight
        color: _button.hovered ? (_button.down ? Theme.bgColorDark : Theme.menuHighlight) : Theme.bgColorLight
        border.color: _button.down ? Theme.colorHighlight : Theme.borderColor
        border.width: Theme.borderWidth
        radius: Theme.buttonRadius
    }
}
