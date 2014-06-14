#ifndef Geo_Database_SQLiteConnectionPropertiesWidget_hpp
#define Geo_Database_SQLiteConnectionPropertiesWidget_hpp

#include "Connection.hpp"
#include "ConnectionPropertiesWidget.hpp"

#include "SQLiteConnection.hpp"

namespace Geo {
namespace Database {
class SQLiteConnectionPropertiesWidget: public ConnectionPropertiesWidget {
  Q_OBJECT

public:
  SQLiteConnectionPropertiesWidget();

  virtual
  ~SQLiteConnectionPropertiesWidget();

  void
  setConnection(Connection::Shared connection) override;

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

#endif // eo_Database_SQLiteConnectionPropertiesWidget_hpp
