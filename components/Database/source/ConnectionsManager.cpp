#include "ConnectionsManager.hpp"

#include "Connection.hpp"


using Geo::Database::ConnectionsManager;
using Geo::Database::Connection;


ConnectionsManager::
ConnectionsManager() {
//  TODO remove later
//  implement xml save/load
  //createConnection();
  //createConnection();
}

QSharedPointer<Connection>
ConnectionsManager::
createConnection() {
  QSharedPointer<Connection> c(new Connection());
  _connections.append(c);

  return c;
}



void
ConnectionsManager::
removeConnection(int i) {
  _connections.remove(i);
}
