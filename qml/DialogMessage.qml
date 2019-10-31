import QtQuick 2.13
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.2
import QtQuick.Window 2.12
import QtQuick.Controls.Material 2.12
import Utils 1.0
import "Style.js" as Style

AbstractMessageDialog {
    id: root


    Pane {
        id: _content

        property real defSpacing: Utils.dp(8)
        property real defOuterSpacing: Utils.dp(16)
        property real buttonsRowImplicitWidth: Screen.pixelDensity * 50

        Material.theme: Style.darkTheme ? Material.Dark : Material.Normal
        Material.accent: Style.accent
        Material.primary: Style.primary
        Material.foreground: Style.foreground
        Material.background: Style.background

        implicitHeight: _contentColumn.implicitHeight + defOuterSpacing * 2
        onImplicitHeightChanged: root.height = implicitHeight
        implicitWidth: Math.min(root.__maximumDimension, Math.max(
            _mainText.implicitWidth, buttonsRowImplicitWidth) + defOuterSpacing * 2);
        onImplicitWidthChanged: root.width = implicitWidth
        focus: root.visible
        Keys.onPressed: {
            event.accepted = true
            if (event.modifiers === Qt.ControlModifier)
                switch (event.key) {
                case Qt.Key_A:
                    _detailedText.selectAll()
                    break
                case Qt.Key_C:
                    _detailedText.copy()
                    break
                case Qt.Key_Period:
                    if (Qt.platform.os === "osx")
                        reject()
                    break
            } else switch (event.key) {
                case Qt.Key_Escape:
                case Qt.Key_Back:
                    reject()
                    break
                case Qt.Key_Enter:
                case Qt.Key_Return:
                    accept()
                    break
            }
        }

        Column {
            id: _contentColumn
            spacing: _content.defSpacing
            x: _content.defOuterSpacing
            y: _content.defOuterSpacing
            width: _content.width - _content.defOuterSpacing * 2

            Item {
                width: parent.width
                height: Math.max(_icon.height, _mainText.height + _informativeText.height) + _content.defSpacing

                Image {
                    id: _icon
                    source: root.standardIconSource
                }

                TextLabel {
                    id: _mainText
                    anchors {
                        left: _icon.right
                        leftMargin: _content.defSpacing * 2
                        right: parent.right
                    }
                    text: root.text
                    font.pointSize: Style.fontPointSize + 2
                    font.weight: Font.Bold
                    wrapMode: Text.WordWrap
                    renderType: Utils.isMobile ? Text.QtRendering : Text.NativeRendering
                }

                TextLabel {
                    id: _informativeText
                    anchors {
                        left: _icon.right
                        right: parent.right
                        top: _mainText.bottom
                        leftMargin: _content.defSpacing * 2
                        topMargin: _content.defSpacing
                    }
                    text: root.informativeText
                    wrapMode: Text.WordWrap
                    renderType: Utils.isMobile ? Text.QtRendering : Text.NativeRendering
                }
            }


            Flow {
                id: _buttons
                spacing: _content.defSpacing
                layoutDirection: Qt.RightToLeft
                width: parent.width - _content.defOuterSpacing
                x: -_content.defOuterSpacing
                Button {
                    id: _okButton
                    text: qsTr("OK")
                    onClicked: root.click(StandardButton.Ok)
                    visible: root.standardButtons & StandardButton.Ok
                }
                Button {
                    id: _openButton
                    text: qsTr("Open")
                    onClicked: root.click(StandardButton.Open)
                    visible: root.standardButtons & StandardButton.Open
                }
                Button {
                    id: _saveButton
                    text: qsTr("Save")
                    onClicked: root.click(StandardButton.Save)
                    visible: root.standardButtons & StandardButton.Save
                }
                Button {
                    id: _saveAllButton
                    text: qsTr("Save All")
                    onClicked: root.click(StandardButton.SaveAll)
                    visible: root.standardButtons & StandardButton.SaveAll
                }
                Button {
                    id: _retryButton
                    text: qsTr("Retry")
                    onClicked: root.click(StandardButton.Retry)
                    visible: root.standardButtons & StandardButton.Retry
                }
                Button {
                    id: _ignoreButton
                    text: qsTr("Ignore")
                    onClicked: root.click(StandardButton.Ignore)
                    visible: root.standardButtons & StandardButton.Ignore
                }
                Button {
                    id: applyButton
                    text: qsTr("Apply")
                    onClicked: root.click(StandardButton.Apply)
                    visible: root.standardButtons & StandardButton.Apply
                }
                Button {
                    id: _yesButton
                    text: qsTr("Yes")
                    onClicked: root.click(StandardButton.Yes)
                    visible: root.standardButtons & StandardButton.Yes
                }
                Button {
                    id: _yesAllButton
                    text: qsTr("Yes to All")
                    onClicked: root.click(StandardButton.YesToAll)
                    visible: root.standardButtons & StandardButton.YesToAll
                }
                Button {
                    id: _noButton
                    text: qsTr("No")
                    onClicked: root.click(StandardButton.No)
                    visible: root.standardButtons & StandardButton.No
                }
                Button {
                    id: _noAllButton
                    text: qsTr("No to All")
                    onClicked: root.click(StandardButton.NoToAll)
                    visible: root.standardButtons & StandardButton.NoToAll
                }
                Button {
                    id: _discardButton
                    text: qsTr("Discard")
                    onClicked: root.click(StandardButton.Discard)
                    visible: root.standardButtons & StandardButton.Discard
                }
                Button {
                    id: _resetButton
                    text: qsTr("Reset")
                    onClicked: root.click(StandardButton.Reset)
                    visible: root.standardButtons & StandardButton.Reset
                }
                Button {
                    id: _restoreDefaultsButton
                    text: qsTr("Restore Defaults")
                    onClicked: root.click(StandardButton.RestoreDefaults)
                    visible: root.standardButtons & StandardButton.RestoreDefaults
                }
                Button {
                    id: _cancelButton
                    text: qsTr("Cancel")
                    onClicked: root.click(StandardButton.Cancel)
                    visible: root.standardButtons & StandardButton.Cancel
                }
                Button {
                    id: _abortButton
                    text: qsTr("Abort")
                    onClicked: root.click(StandardButton.Abort)
                    visible: root.standardButtons & StandardButton.Abort
                }
                Button {
                    id: _closeButton
                    text: qsTr("Close")
                    onClicked: root.click(StandardButton.Close)
                    visible: root.standardButtons & StandardButton.Close
                }
                Button {
                    id: _moreButton
                    text: qsTr("Show Details...")
                    onClicked: content.state = (content.state === "" ? "expanded" : "")
                    visible: root.detailedText.length > 0
                }
                Button {
                    id: _helpButton
                    text: qsTr("Help")
                    onClicked: root.click(StandardButton.Help)
                    visible: root.standardButtons & StandardButton.Help
                }
                onVisibleChildrenChanged: calculateImplicitWidth()
            }
        }

        Item {
            id: _details
            width: parent.width
            implicitHeight: _detailedText.implicitHeight + _content.defSpacing
            height: 0
            clip: true

            anchors {
                left: parent.left
                right: parent.right
                top: _contentColumn.bottom
                topMargin: _content.defSpacing
                leftMargin: _content.defOuterSpacing
                rightMargin: _content.defOuterSpacing
            }

            Flickable {
                id: _flickable
                contentHeight: _detailedText.height
                anchors.fill: parent
                anchors.topMargin: _content.defSpacing
                anchors.bottomMargin: _content.defOuterSpacing

                TextEdit {
                    id: _detailedText
                    color: Style.textColor
                    text: root.detailedText
                    width: _details.width
                    wrapMode: Text.WordWrap
                    readOnly: true
                    selectByMouse: true
                    renderType: Utils.isMobile ? Text.QtRendering : Text.NativeRendering
                }
            }
        }

        states: [
            State {
                name: "expanded"
                PropertyChanges {
                    target: _details
                    height: _content.height - _contentColumn.height - _content.defSpacing - _content.defOuterSpacing
                }
                PropertyChanges {
                    target: _content
                    implicitHeight: _contentColumn.implicitHeight + _content.defSpacing * 2 +
                        _detailedText.implicitHeight + _content.defOuterSpacing * 2
                }
                PropertyChanges {
                    target: _moreButton
                    text: qsTr("Hide Details")
                }
            }
        ]
    }
    function calculateImplicitWidth() {
        if (_buttons.visibleChildren.length < 2)
            return;
        var calcWidth = 0;
        for (var i = 0; i < _buttons.visibleChildren.length; ++i)
            calcWidth += Math.max(100, _buttons.visibleChildren[i].implicitWidth) + _content.defSpacing
        _content.buttonsRowImplicitWidth = _content.defOuterSpacing + calcWidth
    }
    Component.onCompleted: calculateImplicitWidth()
}
