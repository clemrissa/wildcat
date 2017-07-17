#pragma once

#include <memory>
#include <vector>

#include <QtCore/QObject>

namespace Geo
{
namespace Database
{
namespace Connections
{
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

  std::shared_ptr<Connection>
  at(const int i) const { return _connections[i]; }

  std::shared_ptr<Connection>
  operator[](const int i) const { return _connections[i]; }

  std::shared_ptr<Connection>
  createConnection();

  void
  appendConnection(std::shared_ptr<Connection> c);

  void
  removeConnection(int i);

  std::vector<std::shared_ptr<Connection> > const &
  connections() const
  {
    return _connections;
  }

private:
  std::vector<std::shared_ptr<Connection> > _connections;

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
