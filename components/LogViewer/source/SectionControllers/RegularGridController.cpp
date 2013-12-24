#include "RegularGridController"

#include <QPainter>

#include <Geo/Domain/Curve>

#include "../SectionViews/RegularGridView"

#include "ContinuousCurveController"
#include "WellController"

namespace Geo {
namespace LogViewer {
namespace SectionControllers {
RegularGridController::
RegularGridController(AbstractSectionController* well,
                      Domain::Grid::Pointer      grid):
  AbstractGridController(well, grid),
  _view(new SectionViews::RegularGridView(this, grid)) {
  QVectorIterator<Domain::Curve::Pointer> it = _grid->getCurveListIterator();

  while (it.hasNext())
    sectionControllersList.append(new ContinuousCurveController(this,
                                                                it.next()));

  recalculateSize();
}

double
RegularGridController::
topDepth() const {
  return _topDepth;
}

double
RegularGridController::
bottomDepth() const {
  return _bottomDepth;
}

double
RegularGridController::
width() const {
  return _width;
}

void
RegularGridController::
recalculateWidth() {
  _width = _grid->getWidth();
}

SectionViews::AbstractSectionView::Pointer
RegularGridController::
getView() const {
  return _view;
}
}
}
}
