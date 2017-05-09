#include <ComponentManager/ComponentRegistry>

#include "Export.hpp"

#include "BasicMainWindow.hpp"

extern "C" {
Core_PUBLIC void
registerComponent()
{
  using Geo::Core::Private::BasicMainWindow;
  REGISTER_TYPE(BasicMainWindow);
}
}
