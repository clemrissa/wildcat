#ifndef Geo_Database_ConnectionsManager_hpp
#define Geo_Database_ConnectionsManager_hpp

#include <QObject>
#include <QSharedPointer>

namespace Geo {
namespace Database {
class Connection;
class ConnectionsManager: public QObject {
  Q_OBJECT

public:
  Q_INVOKABLE
  ConnectionsManager() {}

  int
  size() { return _connections.size(); }

  QSharedPointer<Connection>
  operator[](const int i) const {
    return _connections[i];
  }

private:
  std::vector<QSharedPointer<Connection> > _connections;
};
}
}

#endif //  Geo_Database_ConnectionsManager_hpp
