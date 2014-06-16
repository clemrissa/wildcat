#include "LogarithmicCurveProxy.hpp"

#include "ContinuousCurveController.hpp"

// #include <Geo/Domain/Log>

namespace Geo {
namespace LogViewer {
namespace SectionControllers {
LogarithmicCurveProxy::
LogarithmicCurveProxy(ContinuousCurveController* curveController):
  AbstractCurveController(0),
  _curveController(curveController)
{
  calculateLog10Data();
  calculateMinMaxValues();
}


AbstractSectionController const*
LogarithmicCurveProxy::
parent() const
{
  return _curveController->parent();
}


double
LogarithmicCurveProxy::
topDepth() const
{
  return _curveController->topDepth();
}


double
LogarithmicCurveProxy::
bottomDepth() const
{
  return _curveController->bottomDepth();
}


double
LogarithmicCurveProxy::
width() const
{
  return _curveController->width();
}


SectionViews::AbstractSectionView::Pointer
LogarithmicCurveProxy::
getView() const
{
  return _curveController->getView();
}


double
LogarithmicCurveProxy::
minValue()
{
  return _minLog10Value;
}


double
LogarithmicCurveProxy::
maxValue()
{
  return _maxLog10Value;
}


void
LogarithmicCurveProxy::
calculateLog10Data()
{
  _curveLog10Data.clear();

  double minimalPossibleValue = -3.0;

  // Domain::Log::Pointer log = _curveController->_curve->getLog();

  // auto it = log->getValuesIterator();

  // while (it.hasNext()) {
  // double x = it.next();

  // if (x <= 0.0)
  // x = minimalPossibleValue;
  // else
  // x = log10(x);

  // _curveLog10Data.append(x);
  // }
}


void
LogarithmicCurveProxy::
calculateMinMaxValues()
{
  // Domain::Log::Pointer log = _curveController->_curve->getLog();
  // auto                 it  = log->getValuesIterator();

  // if (!it.hasNext()) {
  // _minLog10Value = log10(_curveController->minValue());
  // _maxLog10Value = log10(_curveController->maxValue());

  // return;
  // }

  // double minimalPossibleValue = -3.0;

  // double v = minimalPossibleValue;

  // if (_curveController->minValue() > 0.0)
  // v = qMax(minimalPossibleValue, log10(_curveController->maxValue()));

  // _minLog10Value = v;
  // _maxLog10Value = v;

  // QVectorIterator<double> logit(_curveLog10Data);

  // while (logit.hasNext()) {
  // double v = logit.next();

  // if (v > _maxLog10Value)
  // _maxLog10Value = v;

  // if ((v < _minLog10Value) && (v > minimalPossibleValue))
  // _minLog10Value = v;
  // }
}
}
}
}
