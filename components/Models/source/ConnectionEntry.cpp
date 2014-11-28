#include "ConnectionEntry.hpp"

#include <QtGui/QColor>

using Geo::Models::ConnectionEntry;

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
data()
{
  return getDisplayRole();
}


QVariant
ConnectionEntry::
getDisplayRole()
{
  return _connection->textDescription();
}


QVariant
ConnectionEntry::
getDisplayRole(int column)
{
  switch (column) {
  case Type:
    // TODO: change to non-static function
    return Database::Connections::Connection::connectionTypeName(_connection->databaseType());
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

  if (_connection->status() != Database::Connections::Status::Connected)
    return QVariant(QColor(0xFF, 0xBB, 0xBB));

  return QVariant();
}
