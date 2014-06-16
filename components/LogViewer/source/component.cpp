#include "Auxiliary/Visibility.hpp"

#include <DependencyManager/MetaSystem/MetaTypeRegistration>

#include "LogViewerUiFactory.hpp"
#include "LogViewerWidget.hpp"

#include <DependencyManager/MetaSystem/MetaTypeRegistration>

extern "C" {
Geo_LogViewer_PUBLIC void
registerComponent()
{
  REGISTER_TYPE(Geo::LogViewer::LogViewerUiFactory);
  REGISTER_TYPE(Geo::LogViewer::LogViewerWidget);
}
}
