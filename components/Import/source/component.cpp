#include "Auxiliary/Visibility.hpp"

#include <Uni/Logging/Logging>

#include <DependencyManager/MetaSystem/MetaTypeRegistration>

#include "Las/LasFile.hpp"
#include "Las/LasFileParser.hpp"

#include "ImportUiFactory.hpp"
#include "ImportWidget.hpp"
#include <QMenu>

extern "C" {
Geo_Import_PUBLIC void
registerComponent() {
  REGISTER_TYPE(Geo::Import::ImportWidget);
  REGISTER_TYPE(Geo::Import::ImportUiFactory);
  REGISTER_TYPE(Geo::Import::LasFileParser);
  REGISTER_TYPE(Geo::Import::LasFile);
}
}
