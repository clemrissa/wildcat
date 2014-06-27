#ifndef Geo_Database_DatabaseSettingsWidgetModel_ConnectionEntry_hpp
#define Geo_Database_DatabaseSettingsWidgetModel_ConnectionEntry_hpp

#include <Connections/Connection.hpp>
#include <Models/DatabaseSettingsWidgetModel/Entry.hpp>

namespace Geo {
namespace Database {
namespace Models {
namespace DatabaseSettingsWidgetModel {
//

class ConnectionEntry: public Entry {
public:
  ConnectionEntry(Connections::Connection::Shared connection):
    _connection(connection)
  {}

  ConnectionEntry() {}

  QVariant
  data(int role, int column) override;

  Connections::Connection::Shared
  connection()
  {
    return _connection;
  }


private:
  Connections::Connection::Shared _connection;

  QVariant
  getDisplayRole(int column);

  QVariant
  getBackgroundRole(int column);
};

//
}
}
}
}

#endif //  Geo_Database_DatabaseSettingsWidgetModel_ConnectionEntry_hpp
