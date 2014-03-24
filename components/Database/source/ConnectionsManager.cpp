#include "ConnectionsManager.hpp"

#include "Connection.hpp"


using Geo::Database::ConnectionsManager;
using Geo::Database::Connection;


QSharedPointer<Connection>
ConnectionsManager::
createConnection() {
  QSharedPointer<Connection> c(new Connection());
  _connections.push_back(c);

  return c;
}
