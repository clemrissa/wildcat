#ifndef Geo_LogViewer_SectionControllers_AbstractGridController_hpp
#define Geo_LogViewer_SectionControllers_AbstractGridController_hpp

#include <QColor>

#include <Geo/Domain/Grid>

#include "AbstractSectionController.hpp"

namespace Geo {
namespace LogViewer {
namespace SectionControllers {
class WellController;

class AbstractGridController : public AbstractSectionController {
public:
  AbstractGridController(AbstractSectionController* well,
                         Domain::Grid::Pointer      grid);

  bool
  hasDepthLimits() { return true; }

protected:
  Domain::Grid::Pointer _grid;
};
}
}
}

#endif // Geo_LogViewer_SectionControllers_AbstractGridController_hpp
