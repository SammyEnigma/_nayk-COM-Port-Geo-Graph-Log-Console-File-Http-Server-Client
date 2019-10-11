import QtQuick 2.13
import QtQuick.Controls 2.12
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.12
import "Theme.js" as Theme;

ToolBar {
    id: toolBar
    width: parent.width
    height: Theme.fontPixelSize * 2 + 8
    property alias titleText: labelTitle.text
    property alias menuButtonX: toolButtonMenu.x
    property alias menuButtonY: toolButtonMenu.y
    signal menuButtonClick()

    contentItem: Rectangle {
        id: contentItemToolBar
        color: Theme.bgColorLight
        anchors.fill: parent

        RowLayout {
            anchors.fill: parent
            /*
            ToolButton {
                id: toolButtonBack
                text: qsTr("‹")
                onClicked: stack.pop()
            }
            */
            Label {
                id: labelTitle
                text: qsTr("Application Title")
                elide: Label.ElideRight
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                Layout.fillWidth: true
                color: Theme.textColorLight
                font.pixelSize: Theme.fontPixelSize
            }

            ToolButton {
                id: toolButtonMenu
                text: qsTr("⋮")
                font.pixelSize: Theme.fontPixelSize
                onClicked: {
                    toolBar.menuButtonClick()
                }

                contentItem: Text {
                    text: toolButtonMenu.text
                    font: toolButtonMenu.font
                    color: toolButtonMenu.down ? Theme.colorHighlight : Theme.textColorLight
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    elide: Text.ElideRight
                    opacity: enabled ? 1.0 : 0.3
                }

                background: Rectangle {
                    implicitWidth: toolBar.height
                    color: contentItemToolBar.color
                }
            }
        }
    }
}
