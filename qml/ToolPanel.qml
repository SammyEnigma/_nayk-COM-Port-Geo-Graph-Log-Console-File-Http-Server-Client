import QtQuick 2.0
import QtQuick.Controls 2.12
import "Style.js" as Style

ToolBar {
    id: root
    implicitHeight: Style.itemHeight
    implicitWidth: Style.itemWidth

    background: Rectangle {
        id: _bg
        anchors.fill: parent
        color: Style.bgLightColor
    }
}
