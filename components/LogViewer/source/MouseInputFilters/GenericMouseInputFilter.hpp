#ifndef Geo_LogViewer_MouseInputFilters_GenericMouseInputFilter_hpp
#define Geo_LogViewer_MouseInputFilters_GenericMouseInputFilter_hpp

#include "../SectionControllers/AbstractSectionController.hpp"

#include <QMouseEvent>

namespace Geo {
namespace LogViewer {
namespace RenderWidgets {
class GenericRenderWidget;
}

namespace MouseInputFilters {
/// Captures mouse input from
class GenericMouseInputFilter {
public:
  GenericMouseInputFilter(
    RenderWidgets::GenericRenderWidget*                    widget,
    Scalers::Scaler::Pointer                               scaler,
    SectionControllers::AbstractSectionController::Pointer rootSection);

  virtual
  ~GenericMouseInputFilter() {}

  virtual void
  mousePressEvent(QMouseEvent* event) { Q_UNUSED(event); }
  virtual void
  mouseReleaseEvent(QMouseEvent* event) { Q_UNUSED(event); }
  virtual void
  mouseMoveEvent(QMouseEvent* event) { Q_UNUSED(event); }

  virtual void
  resizeEvent(QResizeEvent* event) { Q_UNUSED(event); }

  virtual void
  wheelEvent(QWheelEvent* event) { Q_UNUSED(event); }

protected:
  RenderWidgets::GenericRenderWidget*                           _widget;
  Scalers::Scaler::Pointer                                      _scaler;
  QSharedPointer<SectionControllers::AbstractSectionController> _rootSection;
};
}
}
}

#endif // Geo_LogViewer_MouseInputFilters_GenericMouseInputFilter_hpp
