#ifndef Geo_LogViewer_SectionControllers_MultiWellSection_hpp
#define Geo_LogViewer_SectionControllers_MultiWellSection_hpp

#include "AbstractSectionController.hpp"

// #include <Geo/Domain/LogView>

#include "../Scalers/Scaler.hpp"

namespace Geo {
namespace LogViewer {
namespace SectionViews {
class MultiWellSectionView;
}

namespace SectionControllers {
class MultiWellSectionController: public AbstractSectionController {
public:
  typedef QSharedPointer<MultiWellSectionController> Pointer;

  MultiWellSectionController(AbstractSectionController* parent = 0);

  double
  topDepth() const override;

  double
  bottomDepth() const override;

  double
  width() const override;

  bool
  hasDepthLimits() override { return true; }

  virtual
  SectionViews::AbstractSectionView::Pointer
  getView() const override;

protected:
  void
  recalculateWidth() override;

  // Domain::LogView::Pointer _logView;

  QSharedPointer<SectionViews::MultiWellSectionView> _view;
};
}
}
}

#endif // Geo_LogViewer_SectionControllers_MultiWellSection_hpp
