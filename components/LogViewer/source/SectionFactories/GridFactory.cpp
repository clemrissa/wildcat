#include "GridFactory.hpp"

#include "../SectionControllers/AbstractSectionController.hpp"

#include "../SectionControllers/AbstractGridController.hpp"
#include "../SectionControllers/LogarithmicGridController.hpp"
#include "../SectionControllers/RegularGridController.hpp"

namespace Geo {
namespace LogViewer {
namespace SectionFactories {
SectionControllers::AbstractSectionController*
GridFactory::
createGrid(SectionControllers::AbstractSectionController* parentSection)
{
  // Domain::Grid::Pointer                          grid) {
  SectionControllers::AbstractSectionController* c = nullptr;

  // switch (grid->getType()) {
  // case Domain::Grid::Regular:
  // c = new SectionControllers::
  // RegularGridController(parentSection,
  // grid);

  // break;

  // case Domain::Grid::Logarithmic:
  // c = new SectionControllers::
  // LogarithmicGridController(parentSection,
  // grid);

  // break;
  // }

  // return c;

  return new SectionControllers::
         RegularGridController(parentSection);
}
}
}
}
