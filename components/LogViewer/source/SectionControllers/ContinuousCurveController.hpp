#ifndef Geo_LogViewer_SectionControllers_ContinuousCurveController_hpp
#define Geo_LogViewer_SectionControllers_ContinuousCurveController_hpp

#include <Geo/Domain/Curve>

#include "../SectionViews/AbstractSectionView"

#include "AbstractCurveController"

namespace Geo {
namespace LogViewer {
namespace SectionViews {
class ContinuousCurveView;
}

namespace SectionControllers {
class AbstractGridController;

class ContinuousCurveController: public AbstractCurveController {
public:
  ContinuousCurveController(AbstractGridController* grid,
                            Domain::Curve::Pointer  curve);

public:
  // / @returns top in meters
  double
  topDepth() const override;

  // / @returns bottom in meters
  double
  bottomDepth() const override;

  // / @returns width in in meters
  double
  width() const override;

  bool
  hasDepthLimits() { return true; }

public:
  double
  minValue() override;

  double
  maxValue() override;

  void
  paintHeaderLog10(QPainter&                painter,
                   Scalers::Scaler::Pointer scaler,
                   QRectF&                  rect);

  void
  paintBodyLog10(QPainter&                painter,
                 Scalers::Scaler::Pointer scaler,
                 QRectF&                  rect);

  virtual
  SectionViews::AbstractSectionView::Pointer
  getView() const override;

protected:
  void
  calculateWidth() {}

  void
  calculateMinMaxValues();

  void
  recalculateDepths() {}

private:
  friend class LogarithmicCurveProxy;

  Domain::Curve::Pointer                            _curve;
  QSharedPointer<SectionViews::ContinuousCurveView> _view;

  QVector<double> _curveData;

  double _minValue;
  double _maxValue;
};
}
}
}

#endif // Geo_LogViewer_SectionControllers_ContinuousCurveController_hpp
