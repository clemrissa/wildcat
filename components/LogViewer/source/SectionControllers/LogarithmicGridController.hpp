#ifndef Geo_LogViewer_SectionControllers_LogarithmicGridController_hpp
#define Geo_LogViewer_SectionControllers_LogarithmicGridController_hpp

#include <Geo/Domain/Grid>

#include "AbstractGridController"

#include "../Scalers/Scaler"

namespace Geo {
namespace LogViewer {
namespace SectionViews {
class LogarithmicGridView;
}
namespace SectionControllers {
class LogarithmicGridController: public AbstractGridController {
public:
  LogarithmicGridController(AbstractSectionController* well,
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

  double
  minLog10Value() const;

  double
  maxLog10Value() const;

  virtual
  SectionViews::AbstractSectionView::Pointer
  getView() const override;

private:
  double _minLog10Value;
  double _maxLog10Value;

  // / view
  QSharedPointer<SectionViews::LogarithmicGridView> _view;

  // Domain::Grid::Pointer is defined in AbstactGridController
};
}
}
}

#endif // Geo_LogViewer_SectionControllers_LogarithmicGridController_hpp
