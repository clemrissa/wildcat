#include "Connections/ConnectionManager.hpp"
#include "Connections/SQLiteConnection.hpp"

#include "DatabaseUiFactory.hpp"

#include <QtWidgets/QMenu>

#include <ComponentManager/ComponentRegistry>

#include "Export.hpp"

extern "C"
{

Database_PUBLIC void
registerComponent()
{
  REGISTER_TYPE(QMenu);

  REGISTER_TYPE(Geo::Database::Connections::SQLiteConnection);
  REGISTER_TYPE(Geo::Database::Connections::ConnectionManager);
  REGISTER_TYPE(Geo::Database::DatabaseUiFactory);
}
}
