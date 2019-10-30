import QtQuick 2.13
import QtQuick.Controls 2.12

TextField {
    id: root
    rightPadding: _toolButton.visible ? _toolButton.width + leftPadding : leftPadding
    property alias buttonVisible: _toolButton.visible
    property alias buttonText: _toolButton.text
    signal buttonClicked()

    ToolButton {
        id: _toolButton
        height: root.height - 4
        width: root.height
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.topMargin: 2
        anchors.rightMargin: 2
        text: "..."
        onClicked: root.buttonClicked()
        visible: false
    }
}
