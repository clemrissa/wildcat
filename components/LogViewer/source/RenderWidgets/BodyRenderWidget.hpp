#ifndef Geo_LogViewer_RenderWidgets_BodyRenderWidget_hpp
#define Geo_LogViewer_RenderWidgets_BodyRenderWidget_hpp

#include <QtCore/QSharedPointer>

#include "GenericRenderWidget.hpp"

#include "../MouseInputFilters/BodyMouseInputFilter.hpp"
#include "../SectionControllers/AbstractSectionController.hpp"

namespace Geo {
namespace LogViewer {
namespace RenderWidgets {
class BodyRenderWidget: public GenericRenderWidget {
  Q_OBJECT

public:
  explicit
  BodyRenderWidget(
    Scalers::Scaler::Pointer                               scaler,
    SectionControllers::AbstractSectionController::Pointer rootSection);

  virtual
  ~BodyRenderWidget() {}

protected:
  void
  paintEvent(QPaintEvent* event);

  void
  wheelEvent(QWheelEvent* event);

  void
  mousePressEvent(QMouseEvent* event);

  void
  mouseReleaseEvent(QMouseEvent* event);

  void
  mouseMoveEvent(QMouseEvent* event);

  void
  resizeEvent(QResizeEvent* event);

  // class BodyMouseInputFilter controlls mouse events and LogViewer offsets
  MouseInputFilters::BodyMouseInputFilter _bodyMouseInputFilter;

protected:
  void
  paint(SectionControllers::AbstractSectionController* section,
        QPainter&                                      painter,
        Scalers::Scaler::Pointer                       scaler,
        QRectF                                         rect) override;
};
}
}
}

#endif // Geo_LogViewer_RenderWidgets_BodyRenderWidget_hpp
