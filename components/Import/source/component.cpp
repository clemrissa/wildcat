#include "ImportDialog.hpp"

#include "Auxiliary/Visibility.hpp"

#include <DependencyManager/MetaSystem/MetaTypeRegistration>

extern "C" {
Geo_Import_PUBLIC void
registerComponent() {
  REGISTER_TYPE(Geo::Import::ImportDialog);
}
}
