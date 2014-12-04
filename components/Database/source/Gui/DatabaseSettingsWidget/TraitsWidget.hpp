#ifndef Geo_Database_TraitsWidget_hpp
#define Geo_Database_TraitsWidget_hpp

#include <Gui/Mixin/ConnectionAcceptor.hpp>

namespace Geo {
namespace Database {
namespace Gui {
//

class ConnectionPropertiesWiget;

namespace DatabaseSettingsWidget {
class TraitsWidget:
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
  setConnection(Database::Connections::Connection::Shared connection);

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
#endif //  Geo_Database_TraitsWidget_hpp
