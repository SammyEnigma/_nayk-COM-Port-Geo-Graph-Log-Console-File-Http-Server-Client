import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.12
import QtQuick.Dialogs 1.2
import "Theme.js" as Theme;

Dialog {
    id: dialogAbout
    title: qsTr("About")
    property alias applicationName: textTitle.text
    property alias version: textVersion.text
    property alias buildDate: textDate.text
    property alias author: textAuthor.text
    property alias email: textMail.text

    contentItem: Rectangle {
        color: Theme.bgColor
        anchors.fill: parent

        Text {
            id: textTitle
            width: parent.width
            height: 60
            font.pixelSize: Theme.fontPixelSize + 10
            text: qsTr("Application Title")
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            color: Theme.textColorLight
        }

        GridLayout {
            id: grid
            anchors.top: textTitle.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.topMargin: 30
            anchors.leftMargin: 80
            anchors.rightMargin: 40
            columns: 2
            columnSpacing: 10
            rowSpacing: 10

            Text { text: qsTr("Version:"); color: Theme.textColor; font.pixelSize: Theme.fontPixelSize }
            Text {
                id: textVersion
                text: qsTr("-")
                font.bold: true
                color: Theme.colorHighlight
                font.pixelSize: Theme.fontPixelSize
            }

            Text { text: qsTr("Release date:"); color: Theme.textColor; font.pixelSize: Theme.fontPixelSize }
            Text {
                id: textDate
                text: qsTr("-")
                font.bold: true
                color: Theme.colorHighlight
                font.pixelSize: Theme.fontPixelSize
            }

            Text { text: qsTr("Creator:"); color: Theme.textColor; font.pixelSize: Theme.fontPixelSize }
            Text {
                id: textAuthor
                text: qsTr("Evgeny Teterin")
                font.bold: true
                color: Theme.colorHighlight
                font.pixelSize: Theme.fontPixelSize
            }

            Text { text: qsTr("E-Mail:"); color: Theme.textColor; font.pixelSize: Theme.fontPixelSize }
            Text {
                id: textMail
                text: "<a href=\"mailto:sutcedortal@gmail.com\">sutcedortal@gmail.com</a>"
                font.bold: true
                onLinkActivated: Qt.openUrlExternally(link)
                color: Theme.colorHighlight
                linkColor: Theme.colorHighlight
                font.underline: false
                font.pixelSize: Theme.fontPixelSize

                MouseArea {
                    anchors.fill: parent
                    acceptedButtons: Qt.NoButton
                    cursorShape: parent.hoveredLink ? Qt.PointingHandCursor : Qt.ArrowCursor
                }
            }
        }

        PushButton {
            id: buttonClose
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20
            text: qsTr("Close")
            onClicked: dialogAbout.close()
        }
    }
}
