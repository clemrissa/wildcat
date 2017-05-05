#ifndef Geo_Database_SQLiteConnectionPropertiesWidget_hpp
#define Geo_Database_SQLiteConnectionPropertiesWidget_hpp

#include <Mixin/ConnectionAcceptor.hpp>

#include <Connections/SQLiteConnection.hpp>

namespace Geo {
namespace Database {
namespace Gui {
//

class SQLiteConnectionPropertiesWidget:
  public QWidget,
  public Mixin::ConnectionAcceptor
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