#ifndef Geo_Database_TraitsWidget_hpp
#define Geo_Database_TraitsWidget_hpp

#include <Gui/ConnectionPropertiesWidget.hpp>

namespace Geo {
namespace Database {
namespace Gui {
//

class ConnectionPropertiesWiget;

namespace DatabaseSettingsWidget {
class TraitsWidget: public ConnectionPropertiesWidget
{
  //

public:
  TraitsWidget();

  virtual
  ~TraitsWidget();

  void
  setConnection(Connections::Connection::Shared connection);

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
