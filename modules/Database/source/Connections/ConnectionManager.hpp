#pragma once

#include <QtCore/QObject>
#include <QtCore/QSharedPointer>
#include <QtCore/QVector>

namespace Geo {
namespace Database {
namespace Connections {
//

class Connection;

class ConnectionManager : public QObject
{
  Q_OBJECT

public:
  Q_INVOKABLE
  ConnectionManager();

  int
  size() { return _connections.size(); }

  QSharedPointer<Connection>
  at(const int i) const { return _connections[i]; }

  QSharedPointer<Connection>
  operator[](const int i) const { return _connections[i]; }

  QSharedPointer<Connection>
  createConnection();

  void
  appendConnection(QSharedPointer<Connection> c);

  void
  removeConnection(int i);

  QVector<QSharedPointer<Connection> > const
  connections() const
  {
    return _connections;
  }

private:
  QVector<QSharedPointer<Connection> > _connections;

private slots:
  void
  loadFromXml();

  void
  saveToXml();

  QString
  getDefaultConfigFile() const;
};
}
}
}
