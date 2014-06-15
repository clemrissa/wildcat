#include "SettingsTreeConnection.hpp"

#include <QIcon>
#include <QPalette>
#include <QVariant>

using Geo::Database::SettingsTreeConnection;

QVariant
SettingsTreeConnection::
data(int role, int column)
{
  switch (role) {
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
SettingsTreeConnection::
getForegroundRole(int column)
{
  switch (column) {
  case SettingsTreeEntry::Database:

    if (_connection.isNull())
      return QColor(Qt::lightGray);
    else {
      QPalette palette;
      return QColor(palette.color(QPalette::WindowText));
    }

    break;

  case SettingsTreeEntry::Action:
    return QVariant();
    break;
  }

  return QVariant();
}


QVariant
SettingsTreeConnection::
getDisplayRole(int column)
{
  switch (column) {
  case SettingsTreeEntry::Database:

    if (_connection.isNull())
      return QString("Select DB type to add a connection");
    else
      return _connection->textDescription();

    break;

  case SettingsTreeEntry::Action:
    return QVariant();
    break;
  }

  return QVariant();
}


QVariant
SettingsTreeConnection::
getDecorationRole(int column)
{
  switch (column) {
  case SettingsTreeEntry::Database:
    return QVariant();
    break;

  case SettingsTreeEntry::Action:

    if (!_connection.isNull())
      return QIcon(":/delete.png");
    else
      return QVariant();

    break;
  }

  return QVariant();
}


QVariant
SettingsTreeConnection::
getBackgroundRole(int column)
{
  if (_connection.isNull())
    return QVariant();

  if (_connection->status() != Status::Connected)
    return QVariant(QColor(0xFF, 0xBB, 0xBB));

  return QVariant();
}
