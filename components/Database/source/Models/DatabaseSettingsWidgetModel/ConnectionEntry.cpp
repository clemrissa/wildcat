#include "ConnectionEntry.hpp"

#include <QtCore/QVariant>

#include <QtGui/QIcon>
#include <QtGui/QPalette>

using Geo::Database::Models::DatabaseSettingsWidgetModel::ConnectionEntry;

QVariant
ConnectionEntry::
data(int role, int column)
{
  switch (role) {
  case Qt::DisplayRole:
    return getDisplayRole(column);
    break;

  case Qt::BackgroundRole:
    return getBackgroundRole(column);
    break;

  default:
    return QVariant();
    break;
  }

  return QVariant();
}


QVariant
ConnectionEntry::
getDisplayRole(int column)
{
  switch (column) {
  case Type:
    return _connection->connectionTypeName(_connection->databaseType());
    break;

  case Database:
    return _connection->databasePath();
    break;
  }

  return QVariant();
}


QVariant
ConnectionEntry::
getBackgroundRole(int column)
{
  Q_UNUSED(column);

  if (_connection.isNull())
    return QVariant();

  if (_connection->status() != Connections::Status::Connected)
    return QVariant(QColor(0xFF, 0xBB, 0xBB));

  return QVariant();
}
