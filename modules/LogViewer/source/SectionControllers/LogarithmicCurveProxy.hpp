#ifndef Geo_LogViewer_SectionControllers_LogarithmicCurveProxy_hpp
#define Geo_LogViewer_SectionControllers_LogarithmicCurveProxy_hpp

#include "AbstractCurveController.hpp"

namespace Geo {
namespace LogViewer {
namespace SectionControllers {
class ContinuousCurveController;

class LogarithmicCurveProxy: public AbstractCurveController {
public:
  LogarithmicCurveProxy(ContinuousCurveController* curveController);

  virtual
  ~LogarithmicCurveProxy() {}

public:
  double
  topDepth() const override;

  double
  bottomDepth() const override;

  double
  width() const override;

  bool
  hasDepthLimits() { return true; }

  virtual
  SectionViews::AbstractSectionView::Pointer
  getView() const override;

public:
  AbstractSectionController const*
  parent() const override;

  // actually returns minLog10Value
  double
  minValue() override;

  // actually returns maxLog10Value
  double
  maxValue() override;

private:
  ContinuousCurveController* _curveController;

  QVector<double> _curveLog10Data;

  double _minLog10Value;
  double _maxLog10Value;

  void
  calculateLog10Data();

  void
  calculateMinMaxValues();
};
}
}
}
#endif
