#include "DepthColumnController.hpp"

#include <QPainter>

#include "WellController"

#include "../SectionViews/DepthColumnView"

namespace Geo {
namespace LogViewer {
namespace SectionControllers {
DepthColumnController::
DepthColumnController(AbstractSectionController*   parent,
                      Domain::DepthColumn::Pointer depthColumn)
  : AbstractSectionController(parent),
    _view(new SectionViews::DepthColumnView(this)),
    _depthColumn(depthColumn) {
  recalculateSize();
}

double
DepthColumnController::
topDepth() const {
  return 0.0;
}

double
DepthColumnController::
bottomDepth() const {
  return 0.0;
}

double
DepthColumnController::
width() const {
  return _width;
}

void
DepthColumnController::
recalculateWidth() {
  _width = 0.01; // m
}

SectionViews::AbstractSectionView::Pointer
DepthColumnController::
getView() const {
  return _view;
}
}
}
}
