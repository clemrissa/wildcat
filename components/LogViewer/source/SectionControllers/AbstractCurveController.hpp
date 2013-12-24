#ifndef Geo_LogViewer_SectionControllers_AbstractCurveController_hpp
#define Geo_LogViewer_SectionControllers_AbstractCurveController_hpp

#include <Geo/Domain/Curve>

#include "AbstractSectionController"

namespace Geo {
namespace LogViewer {
namespace SectionControllers {
class AbstractGridController;

class AbstractCurveController : public AbstractSectionController {
public:
  AbstractCurveController(AbstractGridController* gridController);

  virtual
  ~AbstractCurveController() {}

public:
  virtual
  double
  minValue() = 0;

  virtual
  double
  maxValue() = 0;

private:
};
}
}
}
#endif
