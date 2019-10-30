import QtQuick 2.13
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.2
import QtQuick.Controls.Material 2.12
import "Style.js" as Style

Dialog {
    id: root
    title: qsTr("About")

    property alias applicationIcon: _img.source
    property alias applicationTitle: _title.text
    property alias applicationVersion: _textVersion.text
    property alias applicationBuildDate: _textDate.text
    property alias applicationAuthor: _textAuthor.text
    property string applicationMail: "sutcedortal@gmail.com"
    property string applicationUrl: "https://nayk1982.github.io"
    property alias applicationDescription: _descriptionEdit.text

    contentItem: Pane {
        id: _rect

        Material.theme: Style.darkTheme ? Material.Dark : Material.Normal
        Material.accent: Style.accent
        Material.primary: Style.primary
        Material.foreground: Style.foreground
        Material.background: Style.background

        implicitWidth: 400
        implicitHeight: 500
        anchors.fill: parent

        Item {
            id: _headerItem
            height: 64
            width: parent.width
            anchors.top: parent.top
            anchors.topMargin: 30

            Image {
                id: _img
                height: parent.height
                width: height
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: (parent.width - width - _title.contentWidth - 40) / 2
                source: "qrc:/png/about.png"
                horizontalAlignment: Image.AlignHCenter
                verticalAlignment: Image.AlignVCenter
                visible: source !== ""
                fillMode: Image.Stretch
            }

            TextLabel {
                id: _title
                height: parent.height
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: _img.visible ? _img.right : parent.left
                anchors.leftMargin: _img.visible ? 20 : (parent.width - contentWidth) / 2
                text: qsTr("Application Title")
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
                font.pointSize: Style.bigFontPointSize
                font.bold: true
                color: Style.textLightColor
            }
        }

        Row {
            id: _rowVersion
            anchors.top: _headerItem.bottom
            anchors.left: parent.left
            anchors.leftMargin: (parent.width - _labelVersion.width - _textVersion.width) / 2
            anchors.topMargin: 30
            spacing: 10
            visible: _textVersion.text !== ""

            TextLabel {
                id: _labelVersion
                width: 10 + Math.max( contentWidth, _labelDate.contentWidth, _labelAuthor.contentWidth, _labelMail.contentWidth, _labelUrl.contentWidth )
                height: contentHeight * 1.6
                text: qsTr("Version:")
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
            }

            TextLabel {
                id: _textVersion
                width: 10 + Math.max( contentWidth, _textDate.contentWidth, _textAuthor.contentWidth, _textMail.contentWidth, _textUrl.contentWidth )
                height: _labelVersion.height
                font.bold: true
                text: "1.0"
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
                color: Style.textLightColor
            }
        }

        Row {
            id: _rowDate
            anchors.top: _rowVersion.visible ? _rowVersion.bottom : _rowVersion.top
            anchors.left: _rowVersion.left
            spacing: 10
            visible: _textDate.text !== ""

            TextLabel {
                id: _labelDate
                width: _labelVersion.width
                height: _labelVersion.height
                text: qsTr("Build date:")
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
            }

            TextLabel {
                id: _textDate
                width: _textVersion.width
                height: _labelVersion.height
                font.bold: true
                text: "Unknown"
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
                color: Style.textLightColor
            }
        }

        Row {
            id: _rowAuthor
            anchors.top: _rowDate.visible ? _rowDate.bottom : _rowDate.top
            anchors.left: _rowDate.left
            spacing: 10
            visible: _textAuthor.text !== ""

            TextLabel {
                id: _labelAuthor
                width: _labelVersion.width
                height: _labelVersion.height
                text: qsTr("Author:")
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
            }

            TextLabel {
                id: _textAuthor
                width: _textVersion.width
                height: _labelVersion.height
                font.bold: true
                text: qsTr("Evgeniy Teterin")
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
                color: Style.textLightColor
            }
        }

        Row {
            id: _rowMail
            anchors.top: _rowAuthor.visible ? _rowAuthor.bottom : _rowAuthor.top
            anchors.left: _rowAuthor.left
            spacing: 10
            visible: root.applicationMail !== ""

            TextLabel {
                id: _labelMail
                width: _labelVersion.width
                height: _labelVersion.height
                text: qsTr("E-Mail:")
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
            }

            TextLabel {
                id: _textMail
                width: _textVersion.width
                height: _labelVersion.height
                font.bold: true
                font.underline: false
                text: "<a href=\"mailto:" + root.applicationMail + "\">" + root.applicationMail + "</a>"
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
                onLinkActivated: Qt.openUrlExternally(link)
                color: Style.highlightColor
                linkColor: Style.highlightColor

                MouseArea {
                    anchors.fill: parent
                    acceptedButtons: Qt.NoButton
                    cursorShape: parent.hoveredLink ? Qt.PointingHandCursor : Qt.ArrowCursor
                }
            }
        }

        Row {
            id: _rowUrl
            anchors.top: _rowMail.visible ? _rowMail.bottom : _rowMail.top
            anchors.left: _rowMail.left
            spacing: 10
            visible: root.applicationUrl !== ""

            TextLabel {
                id: _labelUrl
                width: _labelVersion.width
                height: _labelVersion.height
                text: qsTr("Web site:")
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
            }

            TextLabel {
                id: _textUrl
                width: _textVersion.width
                height: _labelVersion.height
                font.bold: true
                font.underline: false
                text: "<a href=\"" + root.applicationUrl + "\">" + root.applicationUrl + "</a>"
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
                onLinkActivated: Qt.openUrlExternally(link)
                color: Style.highlightColor
                linkColor: Style.highlightColor

                MouseArea {
                    anchors.fill: parent
                    acceptedButtons: Qt.NoButton
                    cursorShape: parent.hoveredLink ? Qt.PointingHandCursor : Qt.ArrowCursor
                }
            }
        }

        TextArea {
            id: _descriptionEdit
            anchors.top: _rowUrl.visible ? _rowUrl.bottom : _rowUrl.top
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: _btn.top
            anchors.topMargin: 40
            anchors.bottomMargin: 40
            width: parent.width - 40
            text: ""
            visible: text !== ""
            readOnly: true
        }

        OkButton {
            id: _btn
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20
            onClicked: root.close()
        }
    }
}
