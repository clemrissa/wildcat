#ifndef Geo_Database_SQLiteConnectionPropertiesWidget_hpp
#define Geo_Database_SQLiteConnectionPropertiesWidget_hpp

#include <Gui/ConnectionPropertiesWidget.hpp>

#include <Connections/SQLiteConnection.hpp>

namespace Geo {
namespace Database {
namespace Gui {
//

class SQLiteConnectionPropertiesWidget: public ConnectionPropertiesWidget
{
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

  void
  connectSignals();

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
