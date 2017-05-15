#pragma once

#include <Database/Connections/Connection>
#include <QWidget>

namespace Geo {
namespace Database {
namespace Mixin {
//

// some widget which takes Connection to process
class ConnectionAcceptor
{
public:
  virtual
  ~ConnectionAcceptor()
  {
  }

public slots:
  virtual void
  setConnection(Connections::Connection::Shared connection) = 0;
};

//
}
}
}
