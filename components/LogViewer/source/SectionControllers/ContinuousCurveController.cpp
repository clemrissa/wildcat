#include "ContinuousCurveController.hpp"

#include <QPainter>
#include <math.h>

// #include <Geo/Domain/Log>

#include "../Scalers/Scaler.hpp"
#include "../SectionViews/ContinuousCurveView.hpp"
#include "AbstractGridController.hpp"
#include "LogarithmicGridController.hpp"

namespace Geo {
namespace LogViewer {
namespace SectionControllers {
ContinuousCurveController::
ContinuousCurveController(AbstractGridController* grid)
// Domain::Curve::Pointer  curve)
      : AbstractCurveController(grid),
        // _curve(curve),
        _view(new SectionViews::ContinuousCurveView(this))
        // , curve))
{
  // _lineStyle = qrand() % 2 == 1 ? Qt::DotLine : Qt::DashLine;

  calculateMinMaxValues();

  recalculateSize();
}


double
ContinuousCurveController::
topDepth() const
{
  // Domain::Log::Pointer lo = _curve->getLog();

  // return lo->getTopDepth();
}


double
ContinuousCurveController::
bottomDepth() const
{
  // Domain::Log::Pointer lo = _curve->getLog();

  // return lo->getBottomDepth();
}


double
ContinuousCurveController::
width() const
{
  return 0.0;
}


double
ContinuousCurveController::
minValue()
{
  return _minValue;
}


double
ContinuousCurveController::
maxValue()
{
  return _maxValue;
}


void
ContinuousCurveController::
paintHeaderLog10(QPainter&                painter,
                 Scalers::Scaler::Pointer scaler,
                 QRectF&                  rect)
{
  Q_UNUSED(rect);
  Q_UNUSED(painter);
  Q_UNUSED(scaler);

  // QPen pen;
  // pen.setWidthF(_lineWidth);
  // pen.setColor(_color.lighter());
  // pen.setCosmetic(true);
  // pen.setStyle(_lineStyle);

  // painter.setPen(pen);

  // LogarithmicGridController* logarithmicGrid =
  // static_cast<LogarithmicGridController*>(_parent);
  ////    painter.scale(_parent->width() /
  // (LogarithmicGrid->maxLog10Value()
  // - LogarithmicGrid->minLog10Value()), 1.0);
  ////    painter.translate(-LogarithmicGrid->minLog10Value(),
  // 0.0);

  ////    painter.drawLine(QPointF(_minLog10Value, 0.01),
  // QPointF(_maxLog10Value, 0.01));
  // painter.drawLine(QPointF(0.0, 0.01),
  // QPointF(_parent->width(), 0.01));

  // QFont font("Monospace");
  // font.setStyleHint(QFont::TypeWriter);
  // font.setPixelSize(10);
  // painter.setFont(font);
  // painter.setPen(QColor(Qt::gray).darker());
  //// now paint text
  // QTransform t = painter.transform();
  // painter.save();
  // {
  // painter.resetTransform();

  // QPointF p = t.map(QPointF(0.0, 0.0085));
  // painter.translate(p);
  ////        painter.drawText(0.001, 0.0,
  // QString::number(_minValue, 'f',
  // 2));
  // painter.drawText(0.001, 0.0, QString::number(pow(10.0,
  // logarithmicGrid->minLog10Value()), 'f', 2));

  // QFontMetrics metrics = painter.fontMetrics();

  // QString rightValue = QString::number(_maxValue, 'f', 2);

  // double w =
  //
  //
  //
  //
  //
  //
  //
  //
  //
  //
  //
  //
  //
  //
  //
  //
  // scaler->xScaler()->scalePixelsToRealCoords(metrics.width(rightValue));

  // p = t.map(QPointF(_parent->width() - w - 0.001, 0.0085));
  // painter.resetTransform();
  // painter.translate(p);
  // painter.drawText(0.0, 0.0, QString::number(pow(10.0,
  // logarithmicGrid->maxLog10Value()), 'f', 2));
  // }
  // painter.restore();
}


void
ContinuousCurveController::
paintBodyLog10(QPainter&                painter,
               Scalers::Scaler::Pointer scaler,
               QRectF&                  rect)
{
  Q_UNUSED(rect);
  Q_UNUSED(painter);
  Q_UNUSED(scaler);

  // QPen pen;
  // pen.setWidthF(_lineWidth);
  // pen.setColor(_color.lighter());
  // pen.setCosmetic(true);
  // pen.setStyle(_lineStyle);

  // painter.setRenderHint(QPainter::Antialiasing);

  // painter.setPen(pen);

  // LogarithmicGridController* logarithmicGrid =
  // static_cast<LogarithmicGridController*>(_parent);
  // painter.scale(_parent->width() /
  // (logarithmicGrid->maxLog10Value() -
  // logarithmicGrid->minLog10Value()), 1.0);

  // painter.translate(-logarithmicGrid->minLog10Value(), 0.0);

  // QListIterator<QPointF> it(_curveLog10Data);
  // it.next();
  // while(it.hasPrevious() && it.hasNext())
  // {
  // if (it.peekNext().y() < qMax(_parent->topDepth(),
  // rect.top())) {
  // it.next();
  // continue;
  // }
  // if (it.peekPrevious().y() > qMin(_parent->bottomDepth(),
  // rect.bottom())) {
  // break;
  // }

  // painter.drawLine(it.peekPrevious(), it.peekNext());

  // it.next();
  // }
}


void
ContinuousCurveController::
calculateMinMaxValues()
{
  // Domain::Log::Pointer log = _curve->getLog();
  // auto                 it  = log->getValuesIterator();

  // if (!it.hasNext()) {
  // _minValue = 1.0;
  // _maxValue = 10.0;

  // return;
  // }

  // _minValue = it.peekNext();
  // _maxValue = it.peekNext();

  // while (it.hasNext()) {
  // double v = it.next();

  // if (v > _maxValue)
  // _maxValue = v;

  // if (v < _minValue)
  // _minValue = v;
  // }
}


SectionViews::AbstractSectionView::Pointer
ContinuousCurveController::
getView() const
{
  return _view;
}
}
}
}
