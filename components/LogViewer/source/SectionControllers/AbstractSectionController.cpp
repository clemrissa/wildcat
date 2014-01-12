#include "AbstractSectionController.hpp"

#include <limits>

#include <QEvent>

namespace Geo {
namespace LogViewer {
namespace SectionControllers {
AbstractSectionController::
AbstractSectionController(AbstractSectionController* parent):
  _parent(parent)
{}

AbstractSectionController::
~AbstractSectionController() {
  qDeleteAll(sectionControllersList);
}

void
AbstractSectionController::
addChildLogViewerSection(AbstractSectionController* AbstractSectionController)
{
  sectionControllersList.append(AbstractSectionController);

  recalculateSize();
}

AbstractSectionController const*
AbstractSectionController::
parent() const {
  return _parent;
}

void
AbstractSectionController::
recalculateWidth() {
  _width = 0.0;
}

void
AbstractSectionController::
recalculateSize() {
  recalculateWidth();
  recalculateDepths();

  if (_parent)
    _parent->recalculateSize();
}

QListIterator<AbstractSectionController*>
AbstractSectionController::
getChildSectionsIterator() const {
  return QListIterator<AbstractSectionController*>(
    sectionControllersList);
}

void
AbstractSectionController::
recalculateDepths() {
  double max = -std::numeric_limits<double>::max();
  double min = +std::numeric_limits<double>::max();

  int n = 0;

  AbstractSectionController* section;
  foreach(section, sectionControllersList) {
    if (section->hasDepthLimits()) {
      ++n;

      if (section->topDepth() < min)
        min = section->topDepth();

      if (section->bottomDepth() > max)
        max = section->bottomDepth();
    }
  }

  // we have some objects with top and bottom depths
  if (n > 0) {
    _topDepth    = min;
    _bottomDepth = max;
  } else {
    _topDepth    = 0.0;
    _bottomDepth = 100.0;
  }
}

void
AbstractSectionController::
customEvent(QEvent* event) {
  Q_UNUSED(event);
}
}
}
}
