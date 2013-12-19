#include "LogViewerWidget.hpp"
#include "LogViewerWidgetFactory.hpp"

#include "Auxiliary/Visibility.hpp"

#include <DependencyManager/MetaSystem/MetaTypeRegistration>

extern "C" {
Geo_LogViewer_PUBLIC void
registerComponent() {
  REGISTER_TYPE(Geo::LogViewer::LogViewerWidgetFactory);
  REGISTER_TYPE(Geo::LogViewer::LogViewerWidget);
}
}
