#include "Export.hpp"

#include "LogViewerUiFactory.hpp"
#include "LogViewerWidget.hpp"

#include <ComponentManager/ComponentRegistry>

#include "Export.hpp"

extern "C" {
LogViewer_PUBLIC void
registerComponent()
{
  REGISTER_TYPE(Geo::LogViewer::LogViewerUiFactory);
  REGISTER_TYPE(Geo::LogViewer::LogViewerWidget);
}
}
