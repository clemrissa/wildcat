#include "BasicMainWindow.hpp"

#include "Export.hpp"

#include <ComponentManager/ComponentRegistry>

extern "C" {
Core_PUBLIC void
registerComponent()
{
  REGISTER_TYPE(Geo::Core::Private::BasicMainWindow);
}
}
