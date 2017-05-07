#include <QtWidgets/QMenu>

#include <ComponentManager/ComponentRegistry>

#include <Gui/ImportWidget.hpp>

#include "Las/LasFile.hpp"
#include "Las/LasFileParser.hpp"
#include "ImportUiFactory.hpp"

#include "Export.hpp"

extern "C" {
Import_PUBLIC void
registerComponent()
{
  REGISTER_TYPE(Geo::Import::Gui::ImportWidget);
  REGISTER_TYPE(Geo::Import::ImportUiFactory);
  REGISTER_TYPE(Geo::Import::LasFileParser);
  REGISTER_TYPE(Geo::Import::LasFile);
}
}
