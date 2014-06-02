#include "ConnectionsManager.hpp"

#include "SQLiteConnection.hpp"

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

  return c;
}

void
ConnectionsManager::
removeConnection(int i) {
  _connections.remove(i);
}
