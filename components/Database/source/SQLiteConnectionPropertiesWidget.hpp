#ifndef Geo_Database_SQLiteConnectionPropertiesWidget_hpp
#define Geo_Database_SQLiteConnectionPropertiesWidget_hpp

#include "Connection.hpp"
#include <QWidget>

namespace Geo {
namespace Database {
class SQLiteConnectionPropertiesWidget: public QWidget {
public:
  SQLiteConnectionPropertiesWidget();

  virtual
  ~SQLiteConnectionPropertiesWidget();

  void
  setConnection(Connection::Shared connection);

private:
  void
  createUi();

private:
  struct Private;

  Private* p;
};
}
}

#endif // eo_Database_SQLiteConnectionPropertiesWidget_hpp
