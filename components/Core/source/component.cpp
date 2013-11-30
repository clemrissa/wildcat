#include "Private/BasicMainWindow.hpp"

#include "Auxiliary/Visibility.hpp"

#include <DependencyManager/MetaSystem/MetaTypeRegistration>

extern "C" {
Geo_Core_PUBLIC void
registerComponent() {
  REGISTER_TYPE(Geo::Core::Private::BasicMainWindow);
}
}
