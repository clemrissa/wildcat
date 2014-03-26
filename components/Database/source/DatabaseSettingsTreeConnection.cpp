#include "DatabaseSettingsTreeConnection.hpp"


#include <QPalette>


using Geo::Database::DatabaseSettingsTreeConnection;

QVariant
DatabaseSettingsTreeConnection::
data(int role, int column) {
  //if (role != Qt::DisplayRole)
    //return QVariant();


  switch (column) {
  case DatabaseSettingsTreeEntry::Name: 
    switch(role) {
      case Qt::ForegroundRole:
        if (_connection.isNull())
          return QColor(Qt::lightGray);
        else {
          QPalette palette;
          return QColor(palette.color(QPalette::WindowText));
        }
      case Qt::DisplayRole:
        if (_connection.isNull())
          return QString("Select DB type to add a connection");
        else
          return QString("connection");
        break;
    }

  default:
    return QVariant();
    break;
  }

  return QVariant();
}
