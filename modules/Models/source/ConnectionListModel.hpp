#pragma once

#include <QtCore/QAbstractItemModel>
#include <QtCore/QSharedPointer>

#include <Database/Connections/Connection>

namespace Geo {
//
namespace Database {
namespace Connections {
class ConnectionManager;
class Connection;
}
}

//
namespace Models {
//

class ConnectionEntry;

/// TODO: make class abstract, do not link to this library directly
class ConnectionListModel : public QAbstractItemModel
{
public:
  virtual
  ~ConnectionListModel()
  {}

  // public:
  // virtual Database::Connections::Connection::Shared
  // connectionAt(int index) = 0;
};

//
}
}
