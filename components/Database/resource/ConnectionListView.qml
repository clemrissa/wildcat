import QtQuick 2.1
import QtQml.Models 2.1
import QtQuick.Controls 1.0
import QtQuick.Controls.Styles 1.0
import QtQuick.Layouts 1.0

import Connection 1.0
import "ConnectionRoutine.js" as ConnectionRoutine

ColumnLayout {
  id: mainGrid
  spacing: 2

  ToolBar {
    id: toolBar
    anchors.margins: 0
    Layout.fillWidth: true
    layer.enabled: true

    Menu {
      id: dropDownMenu

      MenuItem {
        text: "MySql"
        onTriggered: {
          ConnectionListModel.insertRows(
            ConnectionRoutine.convertToId(0), 0, 1)
        }
      } // MySql
      MenuItem {
        text: "SQLite"
        onTriggered: {
          ConnectionListModel.insertRows(
            ConnectionRoutine.convertToId(1), 0, 1)
        }
      } // MySql
    }

    RowLayout {
      ToolButton {
        id: addConnectionButton
        style: ButtonStyle {
          background: ToolButton {
              implicitWidth: 20
              implicitHeight: 20
              iconSource: "imgs/profile-add-icon.png"
          }
        }
        onClicked: {
          dropDownMenu.popup()
        }
      } // ToolButton
    } // RowLayout
  }

  Rectangle {
    id: table
    anchors.margins: 0
    Layout.fillWidth: true
    Layout.fillHeight: true

    Component {
      id: commonDelegate
      Rectangle {
        property Connection _connection: edit
        //implicitWidth: commonDelegateColumn.width
        width: view.width
        implicitHeight: commonDelegateColumn.implicitHeight
        + 2 * commonDelegateColumn.anchors.margins
        + commonDelegateColumn.spacing
        anchors.margins: 10
        border.color: "red"
        border.width: 1
        radius: 5

        ColumnLayout {
          id: commonDelegateColumn
          anchors.fill: parent
          anchors.margins: 10
          spacing: 2

          RowLayout {
            anchors.fill: parent
            anchors.margins: 0
            spacing: 5

            Text {
              id: databaseType
              Layout.preferredWidth: 80
              anchors.margins: 1
              text: ConnectionRoutine.DatabaseTypeMap[_connection.databaseType]
            }

            Image {
              id: statusImage
              Connections {
                target: _connection
                onStatusChanged: statusImage.source =
                ConnectionRoutine.StatusMap[_connection.status].image
              }
              source: ConnectionRoutine.StatusMap[_connection.status].image
            } //Image
            Text {
              id: statusMessage
              anchors.margins: 1
              Layout.fillWidth: true
              Connections {
                target: _connection
                onStatusChanged: statusMessage.text =
                ConnectionRoutine.composeStatusMessage(_connection.status, _connection.lastError);
              }
              text: ConnectionRoutine.composeStatusMessage(_connection.status, _connection.lastError);
            }
          }
          Text {
            Layout.fillWidth: true
            id: database
            anchors.margins: 1 //1.5 * parent.border.width
            text: _connection.database // "edit" role of the model, to break the binding loop
          }
        }
        Menu {
          id: contextMenu
          property var pos

          MenuItem {
            text: "Connect"
            onTriggered: {
              _connection.connect()
            }
          }

          MenuItem {
            text: "Edit"
            onTriggered: {
              var connectionEditComponent = Qt.createComponent("ConnectionView.qml")
              var errorString = connectionEditComponent.errorString()
              if (errorString == "") {
                var connectionEdit = connectionEditComponent.createObject(null, {
                  "connection": _connection,
                  //"pos": contextMenu.pos
                })
                //connectionEdit.connection = _connection
                connectionEdit.show()
              } else {
                console.log(errorString)
              }
            }
          }

          MenuItem {
            text: "Remove"
            onTriggered: {
              ConnectionListModel.removeRows(index, 1)
            }
          }
        }
        MouseArea {
          id: longPressArea
          anchors.fill: parent
          acceptedButtons: Qt.RightButton
          onClicked: {
            contextMenu.pos = parent.mapToItem(null, longPressArea.mouseX, longPressArea.mouseY)
            contextMenu.popup()
          }
        }
      }
    } // commonDelegate

    ListView {
      id: view
      anchors.fill: parent
      model: DelegateModel {
        id: delegateModel
        model: ConnectionListModel
        delegate: commonDelegate
      }
      spacing: 2
    }

  } // END Rectangle
}
