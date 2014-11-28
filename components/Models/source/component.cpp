#include "ConnectionListModel.hpp"
#include "ConnectionTableModel.hpp"

#include "Auxiliary/Visibility.hpp"

#include <DependencyManager/MetaSystem/MetaTypeRegistration>

extern "C" {
Geo_Models_PUBLIC void
registerComponent()
{
  REGISTER_TYPE(Geo::Models::ConnectionListModel);
  REGISTER_TYPE(Geo::Models::ConnectionTableModel);
}
}
