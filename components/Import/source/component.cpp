#include "Auxiliary/ExecutionControl.hpp"
#include "Auxiliary/Visibility.hpp"

#include <DependencyManager/MetaSystem/MetaTypeRegistration>

#include "ImportDialog.hpp"
#include "ImportUiFactory.hpp"
#include <QMenu>

extern "C" {
Geo_Import_PUBLIC void
registerComponent() {
  INFO << "!!! Component exports its classes";
  REGISTER_TYPE(Geo::Import::ImportDialog);
  REGISTER_TYPE(Geo::Import::ImportUiFactory);
  REGISTER_TYPE(QMenu);
}
}
