#include "MultiWellSectionController.hpp"

#include <limits>

#include <QDebug>
#include <QPainter>
#include <QRectF>

// #include <Geo/Domain/VisualWell>

#include "AbstractSectionController.hpp"
#include "WellController.hpp"

#include "../SectionViews/MultiWellSectionView.hpp"

namespace Geo {
namespace LogViewer {
namespace SectionControllers {
MultiWellSectionController::
MultiWellSectionController(AbstractSectionController* parent):
  AbstractSectionController(parent),
  // _logView(new Domain::LogView()),
  _view(new SectionViews::MultiWellSectionView(this))
{
  // _view(new SectionViews::MultiWellSectionView(this, _logView)) {

  // QVectorIterator<Domain::VisualWell::Pointer> it =
  // _logView->getVisualWellIterator();

  for (int i = 0; i < 2; ++i)
    _sectionControllersList.append(new WellController(this));

  // while (it.hasNext()) {
  // sectionControllersList.append(new WellController(this, it.next()));
  // }

  recalculateSize();
}


double
MultiWellSectionController::
topDepth() const
{
  return _topDepth;
}


double
MultiWellSectionController::
bottomDepth() const
{
  return _bottomDepth;
}


double
MultiWellSectionController::
width() const
{
  return _width;
}


void
MultiWellSectionController::
recalculateWidth()
{
  // empty logView starts at
  // 0.0 meters depth
  if (_sectionControllersList.size() == 0) {
    _width = 0.20; // in  meters
    return;
  }

  _width = 0.0;

  AbstractSectionController* section;
  foreach(section, _sectionControllersList) {
    _width += section->width();
  }

  // extra 1 cm for gap
  // between wells
  _width += (_sectionControllersList.size() - 1) * 0.01;
}


SectionViews::AbstractSectionView::Pointer
MultiWellSectionController::
getView() const
{
  return _view;
}
}
}
}
