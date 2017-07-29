#include "ConnectionEntry.hpp"

#include <QtCore/QVariant>

#include <QtGui/QIcon>
#include <QtGui/QPalette>

#include "Connections/ConnectionUtils.hpp"

using Geo::Database::Gui::ConnectionEntry;

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
    case Column::Database:

      if (!_connection)
        return QColor(Qt::lightGray);
      else
      {
        QPalette palette;
        return QColor(palette.color(QPalette::WindowText));
      }

      break;

    case Column::CloseAction:
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
    case Column::Type:

      if (_connection)
        return ConnectionUtils::connectionTypeName(_connection->databaseType());

      break;

    case Column::Database:

      if (!_connection)
        return QString("Select DB type to add a connection");
      else
        return _connection->databasePath();

      break;

    case Column::CloseAction:
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
    case Column::Database:
      return QVariant();
      break;

    case Column::CloseAction:

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

  if (_connection->status() != IConnection::Status::Connected)
    return QVariant(QColor(0xFF, 0xBB, 0xBB));

  return QVariant();
}
