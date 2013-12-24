#ifndef Geo_LogViewer_SectionControllers_RegularGridController_hpp
#define Geo_LogViewer_SectionControllers_RegularGridController_hpp

#include <Geo/Domain/Grid>

#include "AbstractGridController"

#include "../Scalers/Scaler"

namespace Geo {
namespace LogViewer {
namespace SectionViews {
class RegularGridView;
}
namespace SectionControllers {
class RegularGridController: public AbstractGridController {
public:
  RegularGridController(AbstractSectionController* well,
                        Domain::Grid::Pointer      grid);

public:
  void
  recalculateWidth();

  // / @returns top in meters
  double
  topDepth() const;

  // / @returns bottom in meters
  double
  bottomDepth() const;

  // / @returns width in in meters
  double
  width() const;

  virtual
  SectionViews::AbstractSectionView::Pointer
  getView() const override;

private:
  // view
  QSharedPointer<SectionViews::RegularGridView> _view;

  // Domain::Grid::Pointer is defined in AbstactGridController
};
}
}
}

#endif // Geo_LogViewer_SectionControllers_RegularGridController_hpp
