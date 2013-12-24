#ifndef Geo_LogViewer_SectionControllers_DepthColumnController_hpp
#define Geo_LogViewer_SectionControllers_DepthColumnController_hpp

#include "AbstractSectionController"

#include <Geo/Domain/DepthColumn>

namespace Geo {
namespace LogViewer {
namespace SectionViews {
class DepthColumnView;
}
namespace SectionControllers {
class DepthColumnController: public AbstractSectionController {
public:
  DepthColumnController(AbstractSectionController*   parent,
                        Domain::DepthColumn::Pointer depthColumn);

public:
  // / @returns top in meters
  double
  topDepth() const;

  // / @returns bottom in meters
  double
  bottomDepth() const;

  // / @returns width in in meters
  double
  width() const;

  bool
  hasDepthLimits() { return false; }

  void
  recalculateWidth();

  virtual
  SectionViews::AbstractSectionView::Pointer
  getView() const override;

private:
  QSharedPointer<SectionViews::DepthColumnView> _view;

  Domain::DepthColumn::Pointer _depthColumn;
};
}
}
}

#endif // Geo_LogViewer_SectionControllers_DepthColumnController_hpp
