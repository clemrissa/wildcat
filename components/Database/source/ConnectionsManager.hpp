#ifndef Geo_Database_ConnectionsManager_hpp
#define Geo_Database_ConnectionsManager_hpp

#include <QObject>
#include <QSharedPointer>
#include <QVector>

namespace Geo {
namespace Database {
class Connection;
class ConnectionsManager: public QObject {
  Q_OBJECT

public:
  Q_INVOKABLE
  ConnectionsManager();

  int
  size() {
    return _connections.size();
  }

  QSharedPointer<Connection>
  operator[](const int i) const {
    return _connections[i];
  }

  QSharedPointer<Connection>
  createConnection();

  void
  removeConnection(int i);

  QVector<QSharedPointer<Connection> > const
  connections() const {
    return _connections;
  }

private:
  QVector<QSharedPointer<Connection> > _connections;
};
}
}

#endif //  Geo_Database_ConnectionsManager_hpp
