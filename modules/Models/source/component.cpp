#include "Implementation/ConnectionListModel.hpp"
#include "Implementation/ConnectionTableModel.hpp"

#include "Auxiliary/Visibility.hpp"

#include <DependencyManager/MetaSystem/MetaTypeRegistration>

extern "C" {
Geo_Models_PUBLIC void
registerComponent()
{
  REGISTER_TYPE(Geo::Models::Implementation::ConnectionListModel);
  REGISTER_TYPE(Geo::Models::Implementation::ConnectionTableModel);
}
}
