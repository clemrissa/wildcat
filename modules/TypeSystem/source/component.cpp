#include "TypeSystemUiFactory.hpp"

#include <QMenu>

#include <ComponentManager/ComponentRegistry>

#include "Export.hpp"

extern "C" {
TypeSystem_PUBLIC void
registerComponent()
{
  REGISTER_TYPE(QMenu);

  //REGISTER_TYPE(Geo::TypeSystem::Connections::SQLiteConnection);
  //REGISTER_TYPE(Geo::TypeSystem::Connections::ConnectionManager);
  REGISTER_TYPE(Geo::TypeSystem::TypeSystemUiFactory);
}
}
