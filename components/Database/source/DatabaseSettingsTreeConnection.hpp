#ifndef Geo_Database_DatabaseSettingsTreeConnection_hpp
#define Geo_Database_DatabaseSettingsTreeConnection_hpp

#include "Connection.hpp"
#include "DatabaseSettingsTreeEntry.hpp"

namespace Geo {
namespace Database {
class DatabaseSettingsTreeConnection:
  public DatabaseSettingsTreeEntry {
public:
  DatabaseSettingsTreeConnection(Connection::Shared connection):
    _connection(connection)
  {}

  DatabaseSettingsTreeConnection()
  {}

  QVariant
  data(int role, int column) override;

private:
  Connection::Shared _connection;

  QVariant
  getForegroundRole(int column);

  QVariant
  getDisplayRole(int column);
};
}
}

#endif //  Geo_Database_DatabaseSettingsTreeConnection_hpp
