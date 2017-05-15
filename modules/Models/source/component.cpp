#include "ConnectionListModel.hpp"

#include "Export.hpp"

#include <ComponentManager/ComponentRegistry>

extern "C" {
Models_PUBLIC void
registerComponent()
{
  REGISTER_TYPE(Geo::Models::ConnectionListModel);
}
}
