#include "Auxiliary/Visibility.hpp"

#include <DependencyManager/MetaSystem/MetaTypeRegistration>

#include "ImportDialog.hpp"
#include "UIFactory.hpp"
#include <QMenu>

extern "C" {
Geo_Import_PUBLIC void
registerComponent() {
  REGISTER_TYPE(Geo::Import::ImportDialog);
  REGISTER_TYPE(Geo::Import::UIFactory);
  REGISTER_TYPE(QMenu);
}
}
