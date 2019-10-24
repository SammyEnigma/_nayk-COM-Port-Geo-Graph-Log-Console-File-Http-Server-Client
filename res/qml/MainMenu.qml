import QtQuick 2.13
import QtQuick.Controls 2.12
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.12
import "Theme.js" as Theme;

Menu {
    font.pointSize: Theme.fontPointSize

    background: Rectangle {
        color: Theme.bgColorDark
        border.color: Theme.borderColor
        border.width: Theme.borderWidth
        radius: Theme.buttonRadius
        implicitWidth: Theme.menuWidth
    }
}
