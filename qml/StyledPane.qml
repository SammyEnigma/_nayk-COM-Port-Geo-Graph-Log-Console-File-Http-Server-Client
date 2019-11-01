import QtQuick 2.13
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import "Style.js" as Style

Pane {
    Material.theme: Style.darkTheme ? Material.Dark : Material.Normal
    Material.accent: Style.accent
    Material.primary: Style.primary
    Material.foreground: Style.foreground
    Material.background: Style.background
}
