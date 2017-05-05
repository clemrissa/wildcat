#include "LogarithmicGridController.hpp"

#include <QPainter>

// TODO get rid of math.h, use boost
#include <math.h>

// #include <Geo/Domain/Curve>

#include "../SectionViews/LogarithmicGridView.hpp"

#include "ContinuousCurveController.hpp"
#include "LogarithmicCurveProxy.hpp"
#include "WellController.hpp"

namespace Geo {
namespace LogViewer {
namespace SectionControllers {
LogarithmicGridController::
LogarithmicGridController(AbstractSectionController* well):
  // Domain::Grid::Pointer      grid):
  AbstractGridController(well),
  // AbstractGridController(well, grid),
  _view(new SectionViews::LogarithmicGridView(this))  // , grid))
{
  {
    // QVectorIterator<Domain::Curve::Pointer> it =
    // _grid->getCurveListIterator();

    // while (it.hasNext()) {
    // ContinuousCurveController* c = new ContinuousCurveController(this,
    // it.next());

    // sectionControllersList.append(new LogarithmicCurveProxy(c));
  }

  recalculateSize();
}


double
LogarithmicGridController::
topDepth() const
{
  return _topDepth;
}


double
LogarithmicGridController::
bottomDepth() const
{
  return _bottomDepth;
}


double
LogarithmicGridController::
width() const
{
  return _width;
}


double
LogarithmicGridController::
minLog10Value() const
{
  return _minLog10Value;
}


double
LogarithmicGridController::
maxLog10Value() const
{
  return _maxLog10Value;
}


void
LogarithmicGridController::
recalculateWidth()
{
  _width = 0.06;

  if (_sectionControllersList.size() == 0) {
    _minLog10Value = log10(1.0);
    _maxLog10Value = log10(100.0);

    return;
  }

  AbstractCurveController* curve;

  curve = static_cast<AbstractCurveController*>(_sectionControllersList[0]);

  // here CurveProxy returns Log10 values
  _minLog10Value = curve->minValue();
  _maxLog10Value = curve->maxValue();

  foreach(AbstractSectionController * section, _sectionControllersList) {
    curve = static_cast<AbstractCurveController*>(section);

    if (curve->minValue() < _minLog10Value)
      _minLog10Value = curve->minValue();

    if (curve->maxValue() > _maxLog10Value)
      _maxLog10Value = curve->maxValue();
  }

  // now it could be like [-2.4; 3.7]
}


SectionViews::AbstractSectionView::Pointer
LogarithmicGridController::
getView() const
{
  return _view;
}
}
}
}
