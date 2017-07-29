#pragma once

#include <QtCore/QVariant>

#include <Database/Connections/IConnection>

namespace Geo
{

using Database::IConnection;

namespace Models
{

class ConnectionEntry
{
public:
  enum Column
  {
    Type     = 0,
    Database = 1,
    Size
  };

public:
  ConnectionEntry(std::shared_ptr<IConnection> connection)
    : _connection(connection)
  {}

  QVariant
  data(int role, int column);

  QVariant
  data();

  std::shared_ptr<IConnection>
  connection()
  {
    return _connection;
  }

private:
  std::shared_ptr<IConnection> _connection;

  QVariant
  getDisplayRole();

  QVariant
  getDisplayRole(int column);

  QVariant
  getBackgroundRole(int column);
};

//
}
}
