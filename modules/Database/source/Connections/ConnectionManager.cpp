#include "ConnectionManager.hpp"

#include <QtCore/QTextStream>
#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtCore/QStandardPaths>

#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonValue>
#include <QtCore/QJsonArray>

#include "SQLiteConnection.hpp"
//#include "MongoDBConnection.hpp"

#include "ConnectionUtils.hpp"

namespace Geo
{
namespace Database
{

ConnectionManager::
ConnectionManager()
{
  loadFromJson();
}


std::size_t
ConnectionManager::
size() const
{
  return _connections.size();
}


std::shared_ptr<IConnection>
ConnectionManager::
operator[](std::size_t i) const
{
  return _connections[i];
}


std::vector<std::shared_ptr<IConnection> > const &
ConnectionManager::
connections() const
{
  return _connections;
}


std::shared_ptr<IConnection>
ConnectionManager::
createConnection(DatabaseType databaseType)
{
  std::shared_ptr<IConnection> c;

  switch (databaseType)
  {
    case DatabaseType::SQLite:
      c = std::make_shared<SQLiteConnection>();
      break;

    case DatabaseType::MongoDB:
      //c = std::make_shared<MongoDBConnection>();
      c = std::make_shared<SQLiteConnection>();
      break;

    default:
      c = std::make_shared<SQLiteConnection>();
      break;
  }

  appendConnection(c);

  return c;
}


void
ConnectionManager::
appendConnection(std::shared_ptr<IConnection> c)
{
  connect(c.get(), SIGNAL(databaseChanged(QString)),
          this, SLOT(saveToJson()));

  _connections.push_back(c);

  saveToJson();
}


void
ConnectionManager::
removeConnection(std::size_t i)
{
  _connections.erase(_connections.begin() + i);

  saveToJson();
}


// -------------------------

void
ConnectionManager::
loadFromJson()
{
  QFile file(getDefaultConfigFile());

  if (file.open(QIODevice::ReadOnly))
  {
    QByteArray fileContent = file.readAll();

    QJsonObject jsonSettings = QJsonDocument::fromJson(fileContent).object();

    QJsonArray jsonConnections = jsonSettings["connections"].toArray();

    for (int i = 0; i < jsonConnections.size(); ++i)
    {
      QJsonObject jsonConnection = jsonConnections[i].toObject();

      std::shared_ptr<IConnection> connection =
        ConnectionUtils::restoreConnectionFromJson(jsonConnection);

      if (connection)
        appendConnection(connection);
    }
  }
}


void
ConnectionManager::
saveToJson()
{
  QJsonObject jsonObject;

  QJsonArray connectionJsonArray;

  for (auto connection : _connections)
    connectionJsonArray.append(connection->jsonDescription());

  jsonObject["connections"] = connectionJsonArray;

  QJsonDocument document(jsonObject);

  QByteArray jsonData = document.toJson();

  //--------------

  QString fileName = getDefaultConfigFile();

  QFile file(fileName);

  if (file.open(QIODevice::WriteOnly))
  {
    file.write(jsonData);
  }
}


QString
ConnectionManager::
getDefaultConfigFile() const
{
  QString configLocation =
    QStandardPaths::writableLocation(QStandardPaths::ConfigLocation);

  QString fileName =
    QDir(configLocation).absoluteFilePath("geo.json");

  return fileName;
}


//
}
}
