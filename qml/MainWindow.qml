import QtQuick 2.13
import QtQuick.Controls 2.12
import "Style.js" as Style

ApplicationWindow {
    id: root
    visible: true
    color: Style.bgColor
    title: "Application Title"
    font.pointSize: Style.fontPointSize

    palette {
        alternateBase: Style.bgAlternateColor
        base: Style.bgDarkColor
        button: Style.bgLightColor
        buttonText: Style.textLightColor
        dark: Style.bgDarkColor
        light: Style.menuHighlightColor
        highlight: Style.menuHighlightColor
        highlightedText: Style.textLightColor
        mid: Style.bgDarkColor
        midlight: Style.menuHighlightColor
        shadow: Style.shadowColor
        text: Style.textColor
        window: Style.bgColor
        windowText: Style.textColor
    }
}
