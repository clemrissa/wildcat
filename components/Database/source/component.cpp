#include "Private/ConnectionListModel.hpp"
#include "Private/DatabaseUiFactory.hpp"

#include "Auxiliary/Visibility.hpp"

#include <DependencyManager/MetaSystem/MetaTypeRegistration>

extern "C" {
Geo_Database_PUBLIC void
registerComponent() {
  REGISTER_TYPE(Geo::Database::Private::ConnectionListModel);
  REGISTER_TYPE(Geo::Database::Private::DatabaseUiFactory);
}
}
