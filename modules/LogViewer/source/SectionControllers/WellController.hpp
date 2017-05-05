#ifndef Geo_Logviwer_SectionControllers_WellController_hpp
#define Geo_Logviwer_SectionControllers_WellController_hpp

#include "AbstractSectionController.hpp"

// #include <Geo/Domain/VisualWell>

namespace Geo {
namespace LogViewer {
namespace SectionViews {
class WellView;
}

namespace Scalers {
class Scaler;
}

namespace SectionControllers {
class WellController: public AbstractSectionController {
public:
  WellController(AbstractSectionController* parent);
  // Domain::VisualWell::Pointer visualWell);

  /// @returns top in meters
  virtual double
  topDepth() const;

  /// @returns bottom in meters
  virtual double
  bottomDepth() const;

  /// @returns width in in meters
  virtual double
  width() const;

  bool
  hasDepthLimits() { return true; }

  void
  recalculateWidth();

  virtual
  SectionViews::AbstractSectionView::Pointer
  getView() const override;

private:
  QSharedPointer<SectionViews::WellView> _view;

  // Domain::VisualWell::Pointer _visualWell;
};
}
}
}

#endif // Geo_Logviwer_SectionControllers_WellController_hpp
