#include "Connections/ConnectionManager.hpp"
#include "Connections/SQLiteConnection.hpp"
#include "DatabaseUiFactory.hpp"

// #include "Gui/ConnectionsEditorWidget/ConnectionsEditorWidget.hpp"

#include "Auxiliary/Visibility.hpp"

#include <QMenu>

#include <DependencyManager/MetaSystem/MetaTypeRegistration>

extern "C" {
Geo_Database_PUBLIC void
registerComponent()
{
  REGISTER_TYPE(QMenu);

  REGISTER_TYPE(Geo::Database::Connections::SQLiteConnection);
  REGISTER_TYPE(Geo::Database::Connections::ConnectionManager);
  REGISTER_TYPE(Geo::Database::DatabaseUiFactory);
}
}
