#ifndef Geo_LogViewer_SectionControllers_SaturationColumnController_hpp
#define Geo_LogViewer_SectionControllers_SaturationColumnController_hpp

#include <QColor>

#include "AbstractSectionController"

namespace Geo {
namespace LogViewer {
namespace SectionControllers {
class WellController;

class SaturationColumnController: public AbstractSectionController {
public:
  SaturationColumnController(AbstractSectionController* well);

  // / @returns bottom in meters
  double
  bottomDepth() const;

  // / @returns top in meters
  double
  topDepth() const;

  double
  width() const;

  bool
  hasDepthLimits() { return true; }

  void
  paintHeader(QPainter&                painter,
              Scalers::Scaler::Pointer scaler,
              QRectF&                  rect);

  void
  paintBody(QPainter&                painter,
            Scalers::Scaler::Pointer scaler,
            QRectF&                  rect);

protected:
  QColor _color;

protected:
  void
  recalculateWidth();

  void
  recalculateDepths() {}

private:
  QList<QPointF> _columnData;
};
}
}
}

#endif // Geo_LogViewer_SectionControllers_SaturationColumnController_hpp
