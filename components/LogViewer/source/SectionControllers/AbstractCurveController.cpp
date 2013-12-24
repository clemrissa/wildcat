#include "AbstractCurveController.hpp"

#include "AbstractGridController.hpp"

namespace Geo {
namespace LogViewer {
namespace SectionControllers {
AbstractCurveController::
AbstractCurveController(AbstractGridController* gridController)
  : AbstractSectionController(gridController) {}
}
}
}
