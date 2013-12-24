#include "WellController"

#include <QDebug>
#include <QPainter>
#include <QTime>

// #include <Geo/Domain/DepthColumn>
// #include <Geo/Domain/Grid>

#include "../SectionViews/WellView.hpp"

#include "../SectionFactories/GridFactory.hpp"

#include "DepthColumnController.hpp"
#include "LogarithmicGridController.hpp"
#include "RegularGridController.hpp"
#include "SaturationColumnController.hpp"

namespace Geo {
namespace LogViewer {
namespace SectionControllers {
WellController::
WellController(AbstractSectionController* parent)
// Domain::VisualWell::Pointer visualWell)
  : AbstractSectionController(parent),
    _view(new SectionViews::WellView(this)),
    // _view(new SectionViews::WellView(this, visualWell)),
    // _visualWell(visualWell) {
{
  {
    // first, we take all existing depth columns for current Well
    // QListIterator<Domain::DepthColumn::Pointer> it =
    // _visualWell->getDepthColumnsIterator();

    // while (it.hasNext()) {
    // int order = it.peekNext()->getOrder();

    // DepthColumnController* c = new
    // DepthColumnController(this, it.next());

    qDebug() << "Depth Controller";
    _sectionControllersList.insert(order, c);
    // }
  }

  {
    // QListIterator<Domain::Grid::Pointer> it =
    // _visualWell->getGridsIterator();

    // while (it.hasNext()) {
    // int order = it.peekNext()->getOrder();

    // AbstractSectionController* c =
    // SectionFactories::GridFactory::createGrid(this, it.next());

    // sectionControllersList.insert(order, c);
    // }
  }

  // sectionControllersList.append(new
  // SaturationColumnController(this));
  // sectionControllersList.append(new
  // LogarithmicGridController(this));
  recalculateSize();
}

double
WellController::
bottomDepth() const {
  return _bottomDepth;
}

double
WellController::
topDepth() const {
  return _topDepth;
}

double
WellController::
width() const {
  return _width;
}

void
WellController::
recalculateWidth() {
  _width = 0.0;

  // qDebug() << sectionControllersList.size();

  AbstractSectionController* object;
  foreach(object, sectionControllersList) {
    _width += object->width();
  }
}

SectionViews::AbstractSectionView::Pointer
WellController::
getView() const {
  return _view;
}
}
}
}
