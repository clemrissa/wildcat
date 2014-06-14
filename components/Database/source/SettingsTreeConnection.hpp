#ifndef Geo_Database_SettingsTreeConnection_hpp
#define Geo_Database_SettingsTreeConnection_hpp

#include "Connection.hpp"
#include "SettingsTreeEntry.hpp"

namespace Geo {
namespace Database {
class SettingsTreeConnection: public SettingsTreeEntry {
public:
  SettingsTreeConnection(Connection::Shared connection):
    _connection(connection)
  {}

  SettingsTreeConnection() {}

  QVariant
  data(int role, int column) override;

  Connection::Shared
  connection()
  {
    return _connection;
  }


private:
  Connection::Shared _connection;

  QVariant
  getForegroundRole(int column);

  QVariant
  getDisplayRole(int column);

  QVariant
  getDecorationRole(int column);
};
}
}

#endif //  Geo_Database_SettingsTreeConnection_hpp
