#ifndef Geo_LogViewer_RenderWidgets_HeaderRenderWidget_hpp
#define Geo_LogViewer_RenderWidgets_HeaderRenderWidget_hpp

#include "GenericRenderWidget.hpp"

namespace Geo {
namespace LogViewer {
namespace SectionControllers {
class AbstractSectionController;
}

namespace RenderWidgets {
class HeaderRenderWidget : public GenericRenderWidget {
  Q_OBJECT

public:
  explicit
  HeaderRenderWidget(Scalers::Scaler::Pointer                  scaler,
                     QSharedPointer<SectionControllers::
                                    AbstractSectionController> rootSection);

  virtual
  ~HeaderRenderWidget() {}

protected:
  void
  paintEvent(QPaintEvent* event);

  void
  wheelEvent(QWheelEvent* event);

  void
  timerEvent(QTimerEvent* event);

  void
  mousePressEvent(QMouseEvent* event);

  void
  mouseReleaseEvent(QMouseEvent* event);

  void
  mouseMoveEvent(QMouseEvent* event);

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

#endif // Geo_LogViewer_RenderWidgets_HeaderRenderWidget_hpp
