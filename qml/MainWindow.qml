import QtQuick 2.13
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import "Style.js" as Style

ApplicationWindow {
    id: root
    visible: true
    title: "Application Title"
    Material.theme: Style.darkTheme ? Material.Dark : Material.Normal
    Material.accent: Style.accent
    Material.primary: Style.primary
    Material.foreground: Style.foreground
    Material.background: Style.background
}
