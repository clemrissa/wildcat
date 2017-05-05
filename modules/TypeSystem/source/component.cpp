//#include "Connections/ConnectionManager.hpp"
//#include "Connections/SQLiteConnection.hpp"
#include "TypeSystemUiFactory.hpp"

#include "Auxiliary/Visibility.hpp"

#include <QMenu>

#include <DependencyManager/MetaSystem/MetaTypeRegistration>

extern "C" {
Geo_TypeSystem_PUBLIC void
registerComponent()
{
  REGISTER_TYPE(QMenu);

  //REGISTER_TYPE(Geo::TypeSystem::Connections::SQLiteConnection);
  //REGISTER_TYPE(Geo::TypeSystem::Connections::ConnectionManager);
  REGISTER_TYPE(Geo::TypeSystem::TypeSystemUiFactory);
}
}
