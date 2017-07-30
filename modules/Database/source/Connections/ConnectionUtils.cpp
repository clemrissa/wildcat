#include "ConnectionUtils.hpp"

#include "SQLiteConnection.hpp"
#include "MongoDBConnection.hpp"

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
restoreConnectionFromJson(QJsonObject & jsonConnection)
{
  QString type = jsonConnection["type"].toString();

  if (type == "SQLite")
  {
    return std::make_shared<SQLiteConnection>(jsonConnection);
  }
  else if (type == "MongoDB")
  {
    return std::make_shared<SQLiteConnection>(jsonConnection);
  }

  return std::shared_ptr<IConnection>();
}


//
}
}
}
