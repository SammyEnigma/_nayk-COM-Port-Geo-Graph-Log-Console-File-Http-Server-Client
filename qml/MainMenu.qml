import QtQuick 2.13
import QtQuick.Controls 2.12
import "Style.js" as Style

Menu {
    font.pointSize: Style.fontPointSize
    implicitWidth: Style.itemWidth
    implicitHeight: Style.itemHeight

    background: Rectangle {
        id: _bg
        anchors.fill: parent
        color: Style.bgDarkColor
        border.color: Style.borderColor
        border.width: Style.buttonBorder
        radius: Style.buttonRadius
    }
}
