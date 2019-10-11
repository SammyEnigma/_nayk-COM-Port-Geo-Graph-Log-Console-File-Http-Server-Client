import QtQuick 2.13
import QtQuick.Controls 2.12
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.12
import "Theme.js" as Theme;

MenuSeparator {
    contentItem: Rectangle {
        implicitWidth: Theme.menuWidth
        implicitHeight: 1
        color: Theme.borderColor
    }
}
