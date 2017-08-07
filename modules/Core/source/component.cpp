#include <ComponentManager/ComponentRegistry>

#include "CoreExport.hpp"

#include "BasicMainWindow.hpp"

extern "C" {
Core_PUBLIC void
registerComponent()
{
  using Geo::Core::BasicMainWindow;

  REGISTER_TYPE(BasicMainWindow);
}
}
