#include "Connection.hpp"
#include "DatabaseSettingsWidget.hpp"
#include "DatabaseUiFactory.hpp"

#include "Auxiliary/Visibility.hpp"

#include <QMenu>

#include <DependencyManager/MetaSystem/MetaTypeRegistration>

extern "C" {
Geo_Database_PUBLIC void
registerComponent() {
  REGISTER_TYPE(QMenu);

  REGISTER_TYPE(Geo::Database::Connection);
  REGISTER_TYPE(Geo::Database::DatabaseUiFactory);
  REGISTER_TYPE(Geo::Database::DatabaseSettingsWidget);
}
}
