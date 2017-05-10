#include <ComponentManager/ComponentRegistry>

#include "Export.hpp"

#include <QtWidgets/QMenu>

#include "TypeSystemUiFactory.hpp"

extern "C" {
TypeSystem_PUBLIC void
registerComponent()
{
  REGISTER_TYPE(QMenu);

  REGISTER_TYPE(Geo::TypeSystem::TypeSystemUiFactory);
}
}
