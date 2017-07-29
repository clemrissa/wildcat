#include "ConnectionManager.hpp"

#include <QtCore/QTextStream>
#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtCore/QStandardPaths>

#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>
#include <QtXml/QDomText>

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
  loadFromXml();
}


std::size_t
ConnectionManager::
size() const
{
  return _connections.size();
}


//std::shared_ptr<Connection>
//ConnectionManager::
//at(std::size_t i) const
//{
  //return _connections[i];
//}


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
          this, SLOT(saveToXml()));

  _connections.push_back(c);
  saveToXml();
}


void
ConnectionManager::
removeConnection(std::size_t i)
{
  _connections.erase(_connections.begin() + i);

  saveToXml();
}


// -------------------------

void
ConnectionManager::
loadFromXml()
{
  QDomDocument doc("Connections");

  QFile file(getDefaultConfigFile());

  if (!file.open(QIODevice::ReadOnly))
    return;

  if (!doc.setContent(&file))
  {
    file.close();
    return;
  }

  file.close();

  // ------

  QDomElement docElem = doc.documentElement();

  QDomNode n = docElem.firstChild();

  while (!n.isNull())
  {
    // try to convert the node to an element.
    QDomElement e = n.toElement();

    if (!e.isNull())
    {
      std::shared_ptr<IConnection> connection =
        ConnectionUtils::restoreConnectionFromXml(e);

      if (connection)
        appendConnection(connection);
    }

    n = n.nextSibling();
  }
}


void
ConnectionManager::
saveToXml()
{
  QDomDocument doc("Connections");

  QDomElement root = doc.createElement("Connections");

  doc.appendChild(root);

  for (auto connection : _connections)
    root.appendChild(connection->xmlDescription(doc));

  // -

  QString fileName = getDefaultConfigFile();

  QFile file(fileName);

  if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    return;

  QTextStream out(&file);

  out << doc.toString();
}


QString
ConnectionManager::
getDefaultConfigFile() const
{
  QString configLocation =
    QStandardPaths::writableLocation(QStandardPaths::ConfigLocation);

  QString fileName =
    QDir(configLocation).absoluteFilePath("geo.xml");

  return fileName;
}


//
}
}
