#include "ConnectionUtils.hpp"

#include "SQLiteConnection.hpp"

namespace Geo
{
namespace Database
{
namespace ConnectionUtils
{

QString
connectionTypeName(DatabaseType type)
{
  switch (type)
  {
    case DatabaseType::SQLite:
      return QObject::tr("SQLite");
      break;

    case DatabaseType::MongoDB:
      return QObject::tr("MongoDB");
      break;

    default:
      Q_ASSERT(false);
      break;
  }

  Q_ASSERT(false);
  return QObject::tr("Should not happen");
}


std::shared_ptr<IConnection>
restoreConnectionFromXml(QDomElement& domElement)
{
  QString connectionType = domElement.attribute("Type");

  if (connectionType == "SQLite")
    return std::make_shared<SQLiteConnection>(domElement);

  return std::shared_ptr<IConnection>();
}


//
}
}
}
