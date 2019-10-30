import QtQuick 2.13
import QtQuick.Controls 2.12
import "Style.js" as Style

Button {
    id: root
    text: "Button"
    icon.height: Style.buttonIconSize
    icon.width: Style.buttonIconSize
    implicitWidth: Style.buttonWidth
    implicitHeight: Style.buttonHeight
}
