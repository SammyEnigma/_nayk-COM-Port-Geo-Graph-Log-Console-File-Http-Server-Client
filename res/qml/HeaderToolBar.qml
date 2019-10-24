import QtQuick 2.13
import QtQuick.Controls 2.12
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.12
import "Theme.js" as Theme;

ToolBar {
    id: root
    width: parent.width
    height: Theme.itemHeight
    property alias titleText: _labelTitle.text
    property alias menuButtonX: _toolButtonMenu.x
    property alias menuButtonY: _toolButtonMenu.y
    signal menuButtonClick()

    contentItem: Rectangle {
        id: _contentItemToolBar
        color: Theme.bgColorLight
        anchors.fill: parent

        RowLayout {
            anchors.fill: parent

            Label {
                id: _labelTitle
                text: qsTr("Application Title")
                elide: Label.ElideRight
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                Layout.fillWidth: true
                color: Theme.textColorLight
                font.pointSize: Theme.fontPointSize
            }

            ToolButton {
                id: _toolButtonMenu
                text: qsTr("⋮")
                font.pixelSize: Theme.fontPixelSize
                onClicked: {
                    root.menuButtonClick()
                }

                contentItem: Text {
                    text: _toolButtonMenu.text
                    font: _toolButtonMenu.font
                    color: _toolButtonMenu.down ? Theme.colorHighlight : Theme.textColorLight
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    elide: Text.ElideRight
                    opacity: enabled ? 1.0 : 0.3
                }

                background: Rectangle {
                    implicitWidth: root.height
                    color: _contentItemToolBar.color
                }
            }
        }
    }
}
