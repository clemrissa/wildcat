#include "GenericMouseInputFilter.hpp"

#include "RenderWidgets/GenericRenderWidget.hpp"

namespace Geo {
namespace LogViewer {
namespace MouseInputFilters {
GenericMouseInputFilter::
GenericMouseInputFilter(
  RenderWidgets::GenericRenderWidget*                    widget,
  Scalers::Scaler::Pointer                               scaler,
  SectionControllers::AbstractSectionController::Pointer rootSection):
  _widget(widget),
  _scaler(scaler),
  _rootSection(rootSection)
{}
}
}
}
