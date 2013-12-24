#ifndef Geo_LogViewer_SectionFactories_GridFactory_hpp
#define Geo_LogViewer_SectionFactories_GridFactory_hpp

#include <Geo/Domain/Grid>

namespace Geo {
namespace LogViewer {
namespace SectionControllers {
class AbstractSectionController;
}
namespace SectionFactories {
class GridFactory {
public:
  static
  SectionControllers::AbstractSectionController*
  createGrid(SectionControllers::AbstractSectionController* parentSection,
             Domain::Grid::Pointer                          grid);
};
}
}
}
#endif
