#include "GridFactory"

#include "../SectionControllers/AbstractSectionController"

#include "../SectionControllers/AbstractGridController"
#include "../SectionControllers/LogarithmicGridController"
#include "../SectionControllers/RegularGridController"

namespace Geo {
namespace LogViewer {
namespace SectionFactories {
SectionControllers::AbstractSectionController*
GridFactory::
createGrid(SectionControllers::AbstractSectionController* parentSection,
           Domain::Grid::Pointer                          grid) {
  SectionControllers::AbstractSectionController* c = nullptr;

  switch (grid->getType()) {
  case Domain::Grid::Regular:
    c = new SectionControllers::
        RegularGridController(parentSection,
                              grid);

    break;

  case Domain::Grid::Logarithmic:
    c = new SectionControllers::
        LogarithmicGridController(parentSection,
                                  grid);

    break;
  }

  return c;
}
}
}
}
