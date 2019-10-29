import QtQuick 2.0
import QtQuick.Controls 2.12
import "Style.js" as Style

Text {
    id: root
    property bool light: false
    color: light ? Style.textLightColor : Style.textColor
    font.pointSize: Style.fontPointSize
}
