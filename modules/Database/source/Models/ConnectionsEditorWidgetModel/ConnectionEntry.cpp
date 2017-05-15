#include "ConnectionEntry.hpp"

#include <QtCore/QVariant>

#include <QtGui/QIcon>
#include <QtGui/QPalette>

using Geo::Database::Models::ConnectionsEditorWidgetModel::ConnectionEntry;

QVariant
ConnectionEntry::
data(int role, int column)
{
  switch (role)
  {
    case Qt::ForegroundRole:
      return getForegroundRole(column);
      break;

    case Qt::DisplayRole:
      return getDisplayRole(column);
      break;

    case Qt::DecorationRole:
      return getDecorationRole(column);
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
getForegroundRole(int column)
{
  switch (column)
  {
    case Database:

      if (!_connection)
        return QColor(Qt::lightGray);
      else
      {
        QPalette palette;
        return QColor(palette.color(QPalette::WindowText));
      }

      break;

    case CloseAction:
      return QVariant();
      break;
  }

  return QVariant();
}


QVariant
ConnectionEntry::
getDisplayRole(int column)
{
  switch (column)
  {
    case Type:

      if (_connection)
        return _connection->connectionTypeName(_connection->databaseType());

      break;

    case Database:

      if (!_connection)
        return QString("Select DB type to add a connection");
      else
        return _connection->databasePath();

      break;

    case CloseAction:
      return QVariant();
      break;
  }

  return QVariant();
}


QVariant
ConnectionEntry::
getDecorationRole(int column)
{
  switch (column)
  {
    case Database:
      return QVariant();
      break;

    case CloseAction:

      if (_connection)
        return QIcon(":/delete.png");
      else
        return QVariant();

      break;
  }

  return QVariant();
}


QVariant
ConnectionEntry::
getBackgroundRole(int column)
{
  Q_UNUSED(column);

  if (!_connection)
    return QVariant();

  if (_connection->status() != Connections::Status::Connected)
    return QVariant(QColor(0xFF, 0xBB, 0xBB));

  return QVariant();
}
