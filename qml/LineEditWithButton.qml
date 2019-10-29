import QtQuick 2.13
import QtQuick.Controls 2.12
import "Style.js" as Style

LineEdit {
    id: root
    rightPadding: _toolButton.width + 8
    property alias buttonText: _toolButton.text
    signal buttonClicked()

    PanelButton {
        id: _toolButton
        height: root.height - 2 * Style.buttonBorder - 2
        width: root.height
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.topMargin: Style.buttonBorder + 1
        anchors.rightMargin: Style.buttonBorder + 1
        text: "..."
        onClicked: root.buttonClicked()
    }
}
