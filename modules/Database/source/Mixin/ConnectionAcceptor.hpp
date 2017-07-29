#pragma once

#include <QtWidgets/QWidget>

#include <Database/Connections/IConnection>

namespace Geo
{
namespace Database
{
namespace Mixin
{

// some widget which takes Connection to process
class ConnectionAcceptor
{
public:
  virtual
  ~ConnectionAcceptor() = default;

public slots:

  virtual void
  setConnection(std::shared_ptr<IConnection> connection) = 0;
};

//
}
}
}
