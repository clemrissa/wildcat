#ifndef Geo_Database_SQLiteConnectionPropertiesWidget_hpp
#define Geo_Database_SQLiteConnectionPropertiesWidget_hpp

#include "ConnectionPropertiesWidget.hpp"

#include <Connections/SQLiteConnection.hpp>

namespace Geo {
namespace Database {
namespace Gui {
class SQLiteConnectionPropertiesWidget: public ConnectionPropertiesWidget {
  Q_OBJECT

public:
  SQLiteConnectionPropertiesWidget();

  virtual
  ~SQLiteConnectionPropertiesWidget();

  void
  setConnection(Connections::Connection::Shared connection) override;

private:
  void
  createUi();

private slots:
  void
  onOpenClicked();

  void
  onNewClicked();

private:
  struct Private;

  Private* p;
};
}
}
}

#endif // Geo_Database_SQLiteConnectionPropertiesWidget_hpp
