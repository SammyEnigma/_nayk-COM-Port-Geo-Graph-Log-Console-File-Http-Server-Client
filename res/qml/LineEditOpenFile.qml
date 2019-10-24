import QtQuick 2.13
import QtQuick.Controls 2.12
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.12
import QtQuick.Dialogs 1.2
import "Theme.js" as Theme;

LineEditWithButton {
    id: _lineEdit
    buttonText: qsTr("...")
    onButtonClicked: _fileDialog.open()
    property alias dialogTitle: _fileDialog.title
    property alias folder: _fileDialog.folder
    property alias defaultSuffix: _fileDialog.defaultSuffix
    property alias nameFilters: _fileDialog.nameFilters
    property alias nameFilterIndex: _fileDialog.selectedNameFilterIndex
    property alias selectedNameFilter: _fileDialog.selectedNameFilter
    property alias selectExisting: _fileDialog.selectExisting

    FileDialog {
        id: _fileDialog
        title: qsTr("Please choose a file")
        nameFilters: [ qsTr("All files (*)") ]
        folder: shortcuts.home
        selectMultiple: false
        selectExisting: true
        selectFolder: false
        onAccepted: {
            _lineEdit.text = _fileDialog.fileUrl
        }
    }
}
