#include "DatabaseSettingsTreeConnection.hpp"

#include <QPalette>

using Geo::Database::DatabaseSettingsTreeConnection;

QVariant
DatabaseSettingsTreeConnection::
data(int role, int column) {
  switch (role) {
  case Qt::ForegroundRole:
    return getForegroundRole(column);
    break;

  case Qt::DisplayRole:
    return getDisplayRole(column);
    break;

  default:
    return QVariant();
    break;
  }

  return QVariant();
}

QVariant
DatabaseSettingsTreeConnection::
getForegroundRole(int column) {
  switch (column) {
  case DatabaseSettingsTreeEntry::Database:

    if (_connection.isNull())
      return QColor(Qt::lightGray);
    else {
      QPalette palette;
      return QColor(palette.color(QPalette::WindowText));
    }

    break;

  case DatabaseSettingsTreeEntry::Action:
    return QVariant();
    break;
  }

  return QVariant();
}

QVariant
DatabaseSettingsTreeConnection::
getDisplayRole(int column) {
  switch (column) {
  case DatabaseSettingsTreeEntry::Database:

    if (_connection.isNull())
      return QString("Select DB type to add a connection");
    else
      return _connection->database();

    break;

  case DatabaseSettingsTreeEntry::Action:

    if (!_connection.isNull())
      return QString("-");
    else
      return QVariant();

    break;
  }

  return QVariant();
}
