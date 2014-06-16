#include "AbstractGridController.hpp"

#include "WellController.hpp"

namespace Geo {
namespace LogViewer {
namespace SectionControllers {
AbstractGridController::
AbstractGridController(AbstractSectionController* well)
// Domain::Grid::Pointer      grid)
      : AbstractSectionController(well)

        // _grid(grid)
{}
}
}
}
