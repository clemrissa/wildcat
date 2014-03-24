#include "ConnectionsManager.hpp"

#include "Connection.hpp"


using Geo::Database::ConnectionsManager;
using Geo::Database::Connection;


ConnectionsManager::
ConnectionsManager() {
//  TODO remove later
//  implement xml save/load
  createConnection();
  createConnection();
}

QSharedPointer<Connection>
ConnectionsManager::
createConnection() {
  QSharedPointer<Connection> c(new Connection());
  _connections.push_back(c);

  return c;
}
