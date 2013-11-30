import QtQuick 2.1
import QtQuick.Window 2.1
import QtQuick.Controls 1.0
import QtQuick.Controls.Styles 1.0
import QtQuick.Layouts 1.0
import QtQuick.Dialogs 1.0

import Connection 1.0
import "ConnectionRoutine.js" as ConnectionRoutine

Window {
  id: connectionEdit
  property Connection connection
  property var pos

  width: 400
  height: 200
//  x: pos.x
//  y: pos.y

  title: "Edit " + connection.database

  function updateObject() {
    connection.databaseType = ConnectionRoutine.convertToId(
      databaseTypeInput.currentIndex)
    connection.database = databaseInput.text
  }

  function updateObjectAndClose() {
    updateObject()
    connectionEdit.close()
  }

  GridLayout {
    id: mainGrid
    anchors.margins: 2
    anchors.top: parent.top
    anchors.left: parent.left
    anchors.right: parent.right
    columnSpacing: 2
    rowSpacing: 2
    columns: 3

    Text {
      id: databaseTypeLabel
      text: "Database Type: "
    }


    ComboBox {
      id: databaseTypeInput
      //implicitWidth: 300
      Layout.fillWidth: true
      Layout.columnSpan: 2

      model: ConnectionRoutine.DatabaseTypes
      currentIndex: ConnectionRoutine.convertFromId(connection.databaseType)
      style: ComboBoxStyle { label: Text { text: control.currentText } }
    } // ComboBox

    Text {
      id: databaseLabel
      text: "Database Name: "
    }

    TextField {
      Layout.fillWidth: true
      id: databaseInput
      text: connection.database

      onAccepted: {
        updateObjectAndClose()
      }
      style: TextFieldStyle { }
    }

    Button {
      anchors.margins: 5
      style: ButtonStyle {
        background: Rectangle {
          implicitWidth: 20
          implicitHeight: 20
          color: control.pressed ? "#88003DF5" : control.activeFocus ? "#FFFFFF" : "transparent"
          border.color: "#888888"
          border.width: control.activeFocus ? 0 : 0
          radius: 0
          Image {
            anchors.fill: parent
            source: "imgs/open-file-icon.png"
          } //Image
        } // Rectangle
      } // ButtonStyle
      onClicked: { fileDialog.open() }
    } // Button
  }

  GridLayout {
    id: buttonLayout
    anchors.margins: 2
    anchors.right: parent.right
    anchors.bottom: parent.bottom
    columnSpacing: 2
    rowSpacing: 2
    columns: 2

    Button {
      text: "OK"
      onClicked: {
        updateObjectAndClose()
      }
    }

    Button {
      text: "Cancel"
      onClicked: {
        connectionEdit.close()
      }
    } // button
  }
  FileDialog {
    id: fileDialog
    title: "Please choose a file"
    visible: false
    onAccepted: {
      databaseInput.text = fileDialog.fileUrl.toString()
      close()
    }
    onRejected: {
      close()
    }
    //Component.onCompleted: visible = true
  }
}
