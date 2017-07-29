#pragma once

#include <Mixin/ConnectionAcceptor.hpp>

namespace Geo
{
namespace Database
{
namespace Gui
{
//

class ConnectionPropertiesWiget;

namespace Traits
{
//

class TraitsWidget
  : public QWidget
{
  Q_OBJECT

public:
  TraitsWidget();

  virtual
  ~TraitsWidget();

public slots:

  void
  setConnection(std::shared_ptr<Database::IConnection> connection);

private:
  void
  createUi();

  void
  connectSignals();

private:
  struct Private;

  Private* _p;
};
}

//
}
}
}
