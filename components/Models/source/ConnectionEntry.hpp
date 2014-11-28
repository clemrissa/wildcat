#ifndef Geo_Models_ConnectionEntry_hpp
#define Geo_Models_ConnectionEntry_hpp

#include <QtCore/QVariant>

#include <Database/Connections/Connection>

namespace Geo {
namespace Models {
//

class ConnectionEntry
{
public:
  enum Column { Type     = 0,
                Database = 1,
                Size };

public:
  ConnectionEntry(Database::Connections::Connection::Shared connection):
    _connection(connection)
  {
  }

  QVariant
  data(int role, int column);

  QVariant
  data();

  Database::Connections::Connection::Shared
  connection()
  {
    return _connection;
  }

private:
  Database::Connections::Connection::Shared _connection;


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
#endif //  Geo_Models_ConnectionEntry_hpp
