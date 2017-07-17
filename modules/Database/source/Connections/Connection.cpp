#include "Connection.hpp"

#include "SQLiteConnection.hpp"

#include <QtCore/QString>

using Geo::Database::Connection;
using Geo::Database::SQLiteConnection;

QString
Connection::
connectionTypeName(DatabaseType type)
{
  switch (type)
  {
    case DatabaseType::SQLite:
      return tr("SQLite");
      break;

    case DatabaseType::MongoDB:
      return tr("MongoDB");
      break;

    default:
      Q_ASSERT(false);
      break;
  }

  Q_ASSERT(false);
  return tr("Should not happen");
}


Connection::Shared
Connection::
restoreConnectionFromXml(QDomElement& domElement)
{
  QString connectionType = domElement.attribute("Type");

  if (connectionType == "SQLite")
    return Connection::Shared(new SQLiteConnection(domElement));

  return Connection::Shared(0);
}
