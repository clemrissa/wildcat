#pragma once

#include <Connections/Connection.hpp>
#include <Models/ConnectionsEditorWidgetModel/Entry.hpp>

namespace Geo {
namespace Database {
namespace Models {
namespace ConnectionsEditorWidgetModel {
//

/// Class wraps Connection entity and provides information for
/// table model
class ConnectionEntry : public Entry
{
public:
  enum Column
  {
    Type        = 0,
    Database    = 1,
    CloseAction = 2,
    Size
  };

public:
  ConnectionEntry(Connections::Connection::Shared connection) :
    _connection(connection)
  {}

  ConnectionEntry()
  {}

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
