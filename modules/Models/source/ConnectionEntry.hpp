#pragma once

#include <QtCore/QVariant>

#include <Database/Connections/Connection>

namespace Geo {
namespace Models {

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
  ConnectionEntry(Database::Connection::Shared connection)
    : _connection(connection)
  {}

  QVariant
  data(int role, int column);

  QVariant
  data();

  Database::Connection::Shared
  connection()
  {
    return _connection;
  }

private:
  Database::Connection::Shared _connection;

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
