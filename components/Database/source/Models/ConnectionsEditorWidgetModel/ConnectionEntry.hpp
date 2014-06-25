#ifndef Geo_Database_ConnectionsEditorWidgetModel_Connection_hpp
#define Geo_Database_ConnectionsEditorWidgetModel_Connection_hpp

#include <Connections/Connection.hpp>
#include <Models/ConnectionsEditorWidgetModel/Entry.hpp>

namespace Geo {
namespace Database {
namespace Models {
namespace ConnectionsEditorWidgetModel {
//

class ConnectionEntry: public Entry
{
public:
  ConnectionEntry(Connections::Connection::Shared connection):
    _connection(connection)
  {
  }

  ConnectionEntry()
  {
  }

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
  getForegroundRole(int column);

  QVariant
  getDisplayRole(int column);

  QVariant
  getDecorationRole(int column);

  QVariant
  getBackgroundRole(int column);
};
}
}
}
}

#endif //  Geo_Database_ConnectionsEditorWidgetModel_Connection_hpp
