#ifndef Geo_LogViewer_MouseInputFilters_BodyMouseInputFilter_hpp
#define Geo_LogViewer_MouseInputFilters_BodyMouseInputFilter_hpp

#include "GenericMouseInputFilter.hpp"

namespace Geo {
namespace LogViewer {
namespace MouseInputFilters {
class BodyMouseInputFilter: public GenericMouseInputFilter {
public:
  BodyMouseInputFilter(
    RenderWidgets::GenericRenderWidget* widget,
    Scalers::Scaler::Pointer            scaler,
    SectionControllers::AbstractSectionController::Pointer
    rootSection);

  virtual
  ~BodyMouseInputFilter() {}

  virtual void
  mousePressEvent(QMouseEvent* event);

  virtual void
  mouseReleaseEvent(QMouseEvent* event);

  virtual void
  mouseMoveEvent(QMouseEvent* event);

  virtual void
  resizeEvent(QResizeEvent* event);

  virtual void
  wheelEvent(QWheelEvent* event);

private:
  QPoint _lastPoint;

  void
  xOvershootControl(int offset);

  void
  yOvershootControl(int offset);
};
}
}
}

#endif // #endif // Geo_LogViewer_MouseInputFilters_BodyMouseInputFilter_hpp
