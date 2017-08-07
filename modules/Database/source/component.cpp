#include <ComponentManager/ComponentRegistry>

#include "DatabaseExport.hpp"

#include <QtCore/QDebug>
#include <QtWidgets/QMenu>

#include "DatabaseUiFactory.hpp"

#include "Connections/ConnectionManager.hpp"
#include "Gui/Explorer/ExplorerWidget.hpp"


extern "C"
{

Database_PUBLIC void
registerComponent()
{
  //REGISTER_TYPE(QMenu);

  //using Geo::Database::SQLiteConnection;
  using Geo::Database::ConnectionManager;
  using Geo::Database::DatabaseUiFactory;
  using Geo::Database::Gui::ExplorerWidget;

  //REGISTER_TYPE(SQLiteConnection);
  REGISTER_TYPE(ConnectionManager);
  REGISTER_TYPE(DatabaseUiFactory);
  REGISTER_TYPE(ExplorerWidget);
}
}
