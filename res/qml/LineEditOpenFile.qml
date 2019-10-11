import QtQuick 2.13
import QtQuick.Controls 2.12
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.12
import QtQuick.Dialogs 1.2
import "Theme.js" as Theme;

LineEditWithButton {
    id: lineEdit
    buttonText: qsTr("...")
    onButtonClicked: fileDialog.open()
    property alias dialogTitle: fileDialog.title
    property alias folder: fileDialog.folder
    property alias defaultSuffix: fileDialog.defaultSuffix
    property alias nameFilters: fileDialog.nameFilters
    property alias nameFilterIndex: fileDialog.selectedNameFilterIndex
    property alias selectedNameFilter: fileDialog.selectedNameFilter
    property alias selectExisting: fileDialog.selectExisting

    FileDialog {
        id: fileDialog
        title: qsTr("Please choose a file")
        nameFilters: [ qsTr("All files (*)") ]
        folder: shortcuts.home
        selectMultiple: false
        selectExisting: true
        selectFolder: false
        onAccepted: {
            lineEdit.text = fileDialog.fileUrl
        }
    }
}
