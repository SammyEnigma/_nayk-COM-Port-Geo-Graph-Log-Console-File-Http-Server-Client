import QtQuick 2.13
import QtQuick.Window 2.13
import QtQuick.Controls 2.12
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.12
import "Theme.js" as Theme;

ApplicationWindow {
    id: _appWindow
    visible: true
    width: 640
    height: 480
    color: Theme.bgColor
    title: qsTr("Application Title")
    font.pointSize: Theme.fontPointSize

    palette {
        alternateBase: Theme.bgColorAlternate
        base: Theme.bgColorDark
        button: Theme.bgColorLight
        buttonText: Theme.textColorLight
        dark: Theme.bgColorDark
        light: Theme.menuHighlight
        highlight: Theme.menuHighlight
        highlightedText: Theme.textColorLight
        mid: Theme.bgColorDark
        midlight: Theme.menuHighlight
        shadow: Theme.shadow
        text: Theme.textColor
        window: Theme.bgColor
        windowText: Theme.textColor
    }
}
