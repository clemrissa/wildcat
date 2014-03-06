#include "Auxiliary/Visibility.hpp"

#include <Uni/Logging/Logging>

#include <DependencyManager/MetaSystem/MetaTypeRegistration>

#include "ImportUiFactory.hpp"
#include "ImportWidget.hpp"
#include <QMenu>

extern "C" {
Geo_Import_PUBLIC void
registerComponent() {
  INFO << "!!! Component exports its classes";
  REGISTER_TYPE(Geo::Import::ImportWidget);
  REGISTER_TYPE(Geo::Import::ImportUiFactory);
  REGISTER_TYPE(QMenu);
}
}
