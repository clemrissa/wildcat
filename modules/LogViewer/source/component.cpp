#include <ComponentManager/ComponentRegistry>

#include "Export.hpp"

#include "LogViewerUiFactory.hpp"
#include "LogViewerWidget.hpp"

extern "C" {
LogViewer_PUBLIC void
registerComponent()
{
  using Geo::LogViewer::LogViewerUiFactory;
  using Geo::LogViewer::LogViewerWidget;

  REGISTER_TYPE(LogViewerUiFactory);
  REGISTER_TYPE(LogViewerWidget);
}
}
