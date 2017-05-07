#include "Implementation/ConnectionListModel.hpp"
#include "Implementation/ConnectionTableModel.hpp"

#include "Export.hpp"

#include <ComponentManager/ComponentRegistry>

extern "C" {
Models_PUBLIC void
registerComponent()
{
  REGISTER_TYPE(Geo::Models::Implementation::ConnectionListModel);
  REGISTER_TYPE(Geo::Models::Implementation::ConnectionTableModel);
}
}
