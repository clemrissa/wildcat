#include <ComponentManager/ComponentRegistry>

#include "DatabaseExport.hpp"

#include <QtWidgets/QMenu>

#include "DatabaseUiFactory.hpp"

#include "Connections/ConnectionManager.hpp"

#include "Connections/SQLiteConnection.hpp"

#include <QtCore/QDebug>

extern "C"
{

Database_PUBLIC void
registerComponent()
{
  //REGISTER_TYPE(QMenu);

  using Geo::Database::SQLiteConnection;
  using Geo::Database::ConnectionManager;
  using Geo::Database::DatabaseUiFactory;

  REGISTER_TYPE(SQLiteConnection);
  REGISTER_TYPE(ConnectionManager);
  REGISTER_TYPE(DatabaseUiFactory);
}
}
