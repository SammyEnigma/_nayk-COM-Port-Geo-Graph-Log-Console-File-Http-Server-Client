import QtQuick 2.0
import QtQuick.Controls 2.12
import "Theme.js" as Theme;

Text {
    id: root
    property bool light: false
    color: light ? Theme.textColorLight : Theme.textColor
    font.pointSize: Theme.fontPointSize
}
