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

  QVariant
  data(int role, int column) override;

private:
  Connection::Shared _connection;
};
}
}

#endif //  Geo_Database_DatabaseSettingsTreeConnection_hpp
