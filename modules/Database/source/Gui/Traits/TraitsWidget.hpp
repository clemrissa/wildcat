#pragma once

#include <Mixin/ConnectionAcceptor.hpp>

namespace Geo {
namespace Database {
namespace Gui {
//

class ConnectionPropertiesWiget;

namespace Traits {
//

class TraitsWidget :
  public QWidget,
  public Mixin::ConnectionAcceptor
{
  Q_OBJECT

public:
  TraitsWidget();

  virtual
  ~TraitsWidget();

public slots:
  void
  setConnection(Database::Connections::Connection::Shared connection) override;

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
