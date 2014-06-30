#ifndef Geo_Database_DatabasePropertiesWidget_hpp
#define Geo_Database_DatabasePropertiesWidget_hpp

#include <Gui/ConnectionPropertiesWidget.hpp>

namespace Geo {
namespace Database {
namespace Gui {
class ConnectionPropertiesWiget;

namespace DatabaseSettingsWidget {
class DatabasePropertiesWidget: public ConnectionPropertiesWidget
{
  //

public:
  DatabasePropertiesWidget();

  virtual
  ~DatabasePropertiesWidget();

  void
  setConnection(Connections::Connection::Shared connection);

private:
  void
  createUi();

private:
  struct Private;

  Private* _p;
};
}
}
}
}
#endif //  Geo_Database_DatabasePropertiesWidget_hpp
