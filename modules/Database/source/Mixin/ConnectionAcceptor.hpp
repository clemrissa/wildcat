#pragma once

#include <QtWidgets/QWidget>

#include <Database/Connections/Connection>

namespace Geo
{
namespace Database
{
namespace Mixin
{
//

// some widget which takes Connection to process
class ConnectionAcceptor
{
public:
  virtual
  ~ConnectionAcceptor()
  {}

public slots:

  virtual void
  setConnection(Connection::Shared connection) = 0;
};

//
}
}
}
