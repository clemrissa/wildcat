#ifndef Geo_Database_DatabasePropertiesWidget_hpp
#define Geo_Database_DatabasePropertiesWidget_hpp

#include "ConnectionPropertiesWidget.hpp"

namespace Geo {
namespace Database {
namespace Gui {
class DatabasePropertiesWidget: public ConnectionPropertiesWidget {
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

  Private* p;
};
}
}
}
#endif //  Geo_Database_DatabasePropertiesWidget_hpp
