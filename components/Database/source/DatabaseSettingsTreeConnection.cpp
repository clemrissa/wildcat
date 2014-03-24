#include "DatabaseSettingsTreeConnection.hpp"

using Geo::Database::DatabaseSettingsTreeConnection;

QVariant
DatabaseSettingsTreeConnection::
data(int role, int column) {
  if (role != Qt::DisplayRole)
    return QVariant();

  switch (column) {
  case DatabaseSettingsTreeEntry::Name:
    return QString("connection");
    break;

  default:
    return QVariant();
    break;
  }

  return QVariant();
}
