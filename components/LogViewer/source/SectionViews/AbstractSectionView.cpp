#include "AbstractSectionView.hpp"

#include <QEvent>
#include <limits>

#include "../SectionControllers/AbstractSectionController.hpp"

namespace Geo {
namespace LogViewer {
namespace SectionViews {
AbstractSectionView::
AbstractSectionView(
  SectionControllers::AbstractSectionController* controller):
  _controller(controller)
{}

SectionControllers::AbstractSectionController const*
AbstractSectionView::
controller() const {
  return _controller;
}
}
}
}
