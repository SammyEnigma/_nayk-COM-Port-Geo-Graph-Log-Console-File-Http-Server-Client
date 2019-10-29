import QtQuick 2.13
import QtQuick.Controls 2.12
import "Style.js" as Style

MenuSeparator {
    id: root
    implicitWidth: Style.itemWidth
    implicitHeight: Style.buttonBorder

    contentItem: Rectangle {
        anchors.fill: parent
        color: Style.borderColor
    }
}
