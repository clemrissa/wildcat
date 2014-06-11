#include "ConnectionsManager.hpp"

#include "SQLiteConnection.hpp"

#include <QDir>
#include <QDomDocument>
#include <QDomElement>
#include <QDomText>
#include <QFile>
#include <QStandardPaths>
#include <QTextStream>

#include <Uni/Logging/Logging>

using Geo::Database::Connection;
using Geo::Database::ConnectionsManager;

ConnectionsManager::
ConnectionsManager() {
  //  TODO remove later
  //  implement xml save/load
}

QSharedPointer<Connection>
ConnectionsManager::
createConnection() {
  QSharedPointer<Connection> c(new SQLiteConnection());

  _connections.append(c);

  storeToXml();

  return c;
}

void
ConnectionsManager::
removeConnection(int i) {
  _connections.remove(i);
}

void
ConnectionsManager::
loadFromXml() {
  //
}

void
ConnectionsManager::
storeToXml() {
  QDomDocument doc("Connections");

  QDomElement root = doc.createElement("Connections");
  doc.appendChild(root);

  for (auto connection : _connections)
    root.appendChild(connection->xmlDescription(doc));

  QString xml = doc.toString();

  QString fileName = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation);

  fileName = QDir(QStandardPaths::writableLocation(QStandardPaths::ConfigLocation)).absoluteFilePath("geo.xml");

  QFile file(fileName);

  if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    return;

  QTextStream out(&file);

  out << xml;
}
