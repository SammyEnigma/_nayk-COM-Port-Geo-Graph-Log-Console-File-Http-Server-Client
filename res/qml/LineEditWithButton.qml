import QtQuick 2.13
import QtQuick.Controls 2.12
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.12
import "Theme.js" as Theme;

LineEdit {
    id: _lineEdit
    rightPadding: _toolButton.width + 10
    property alias buttonText: _toolButton.text
    signal buttonClicked()

    ToolButton {
        id: _toolButton
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.topMargin: Theme.borderWidth + 1
        anchors.rightMargin: Theme.borderWidth + 1
        text: qsTr("...")
        onClicked: {
            _lineEdit.buttonClicked()
        }

        font.pointSize: Theme.fontPointSize
        implicitHeight: _lineEdit.height - 2 * Theme.borderWidth - 2
        implicitWidth: _lineEdit.height
        opacity: enabled ? 1.0 : 0.3

        contentItem: Text {
            text: _toolButton.text
            font: _toolButton.font
            color: _toolButton.down ? Theme.colorHighlight : Theme.textColorLight
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            elide: Text.ElideRight
        }

        background: Rectangle {
            anchors.fill: parent
            color: _toolButton.hovered ? (_toolButton.down ? Theme.bgColorDark : Theme.menuHighlight) : Theme.bgColorLight
            border.color: Theme.menuHighlight
            border.width: 1
            radius: Theme.buttonRadius - 3
        }
    }
}
