import QtQuick 2.13
import QtQuick.Controls 2.12
import Utils 1.0
import "Style.js" as Style

Button {
    id: root
    text: "Button"

    icon.height: Utils.dp( Style.buttonIconSize )
    icon.width: Utils.dp( Style.buttonIconSize )
    implicitWidth: Utils.dp( Style.buttonWidth )
    implicitHeight: Utils.dp( Style.buttonHeight )
}
