#include "ContinuousCurveView.hpp"

#include <QtGui/QPainter>
#include <QtGui/QPolygon>

#include <QDebug>

#include <math.h>

// #include <Geo/Domain/Log>

#include "../SectionControllers/AbstractSectionController.hpp"
#include "../SectionControllers/ContinuousCurveController.hpp"
#include "../SectionControllers/LogarithmicGridController.hpp"

#include "../Scalers/Scaler.hpp"

namespace Geo {
namespace LogViewer {
namespace SectionViews {
ContinuousCurveView::
ContinuousCurveView(SectionControllers::AbstractSectionController* controller):
  // Domain::Curve::Pointer                         curve):
  AbstractSectionView(controller)
  // _curve(curve)
{
  // _lineStyle = qrand() % 2 == 1 ? Qt::DotLine : Qt::DashLine;
}


void
ContinuousCurveView::
paintHeader(QPainter&                painter,
            Scalers::Scaler::Pointer scaler,
            QRectF&                  rect)
{
  Q_UNUSED(rect);

  // horisontal curve line in header
  {
    QPen pen;
    // pen.setWidthF(_curve->getThickness());
    // pen.setColor(_curve->getColor());
    pen.setCosmetic(true);
    // pen.setStyle(_lineStyle);

    painter.setRenderHint(QPainter::Antialiasing);

    painter.setPen(pen);

    painter.drawLine(QPointF(0.0,
                             0.01),
                     QPointF(_controller->parent()->width(), 0.01));
  }

  QFont
    font("Monospace");

  font.setStyleHint(QFont::TypeWriter);
  font.setPixelSize(10);
  painter.setFont(font);
  painter.setPen(QColor(Qt::gray).darker());
  // now paint text
  QTransform t = painter.transform();
  painter.save();
  {
    painter.resetTransform();

    QPointF p = t.map(QPointF(0.0, 0.0085));
    painter.translate(p);

    SectionControllers::AbstractCurveController* curveController =
      static_cast<SectionControllers::AbstractCurveController*>(_controller);
    painter.drawText(0.001, 0.0,
                     QString::number(curveController->minValue(), 'f', 2));

    QFontMetrics metrics = painter.fontMetrics();

    QString rightValue = QString::number(curveController->maxValue(), 'f', 2);

    double w =
      scaler->xScaler()->scalePixelsToRealCoords(metrics.width(
                                                   rightValue));

    p = t.map(QPointF(_controller->parent()->width() - w - 0.001, 0.0085));
    painter.resetTransform();
    painter.translate(p);
    painter.drawText(0.0, 0.0,
                     QString::number(curveController->maxValue(), 'f', 2));
  }
  painter.restore();
}


void
ContinuousCurveView::
paintHeaderLog10(QPainter&                painter,
                 Scalers::Scaler::Pointer scaler,
                 QRectF&                  rect)
{
  Q_UNUSED(rect);

  QPen pen;
  // pen.setWidthF(_curve->getThickness());
  // pen.setColor(_curve->getColor());
  // pen.setCosmetic(true);
  // pen.setStyle(_lineStyle);

  painter.setPen(pen);

  // TODO
  const SectionControllers::LogarithmicGridController*
  logarithmicGridController =
    static_cast<const SectionControllers::LogarithmicGridController*>(
      _controller->parent());
  // painter.scale(_controller->parent()->width() /
  // (LogarithmicGrid->getMaxLog10Value() -
  // LogarithmicGrid->getMinLog10Value()), 1.0);
  // painter.translate(-LogarithmicGrid->getMinLog10Value(), 0.0);

  // painter.drawLine(QPointF(_minLog10Value, 0.01),
  // QPointF(_maxLog10Value,
  // 0.01));
  painter.drawLine(QPointF(0.0,
                           0.01),
                   QPointF(_controller->parent()->width(), 0.01));

  QFont
    font("Monospace");

  font.setStyleHint(QFont::TypeWriter);
  font.setPixelSize(10);
  painter.setFont(font);
  painter.setPen(QColor(Qt::gray).darker());
  // now paint text
  QTransform t = painter.transform();
  painter.save();
  {
    painter.resetTransform();

    QPointF p = t.map(QPointF(0.0, 0.0085));
    painter.translate(p);

    painter.drawText(0.001, 0.0,
                     QString::number(pow(10.0,
                                         logarithmicGridController->
                                         minLog10Value()), 'f', 2));

    QFontMetrics metrics = painter.fontMetrics();

    // QString rightValue = QString::number(_maxValue, 'f', 2);
    QString rightValue;

    double w =
      scaler->xScaler()->scalePixelsToRealCoords(metrics.width(
                                                   rightValue));

    p =
      t.map(QPointF(_controller->parent()->width() - w - 0.001,
                    0.0085));
    painter.resetTransform();
    painter.translate(p);
    painter.drawText(0.0, 0.0,
                     QString::number(pow(10.0,
                                         logarithmicGridController->
                                         maxLog10Value()), 'f', 2));
  }
  painter.restore();
}


void
ContinuousCurveView::
paintBody(QPainter&                painter,
          Scalers::Scaler::Pointer scaler,
          QRectF&                  rect)
{
  // Q_UNUSED(scaler);

  // QPen pen;
  // pen.setWidthF(_curve->getThickness());
  // pen.setColor(_curve->getColor());
  // pen.setCosmetic(true);
  //// pen.setStyle(_lineStyle);

  // painter.setRenderHint(QPainter::Antialiasing);

  // painter.setPen(pen);
  // SectionControllers::ContinuousCurveController* curveController =
  // static_cast<SectionControllers::ContinuousCurveController*>(_controller);
  // painter.scale(_controller->parent()->width() /
  // (curveController->maxValue() - curveController->minValue()),
  // 1.0);

  // painter.translate(-curveController->minValue(), 0.0);

  // auto lo = _curve->getLog();

  //// we must determine lower and upper index
  // int topIndex;
  // int bottomIndex;
  // {
  // double minPaintingDepth =
  // qMax(_controller->parent()->topDepth(), rect.top());

  // double maxPaintingDepth =
  // qMin(_controller->parent()->bottomDepth(), rect.bottom());

  // topIndex = int((minPaintingDepth - lo->getTopDepth()) / lo->getStep());

  // if (topIndex < 0)
  // topIndex = 0;

  // bottomIndex = int((maxPaintingDepth - lo->getTopDepth()) / lo->getStep());

  // if (bottomIndex < 0)
  // bottomIndex = 0;

  // if (bottomIndex > lo->getCount() - 1)
  // bottomIndex = lo->getCount();
  // }

  // QPolygonF       polygon;
  // QVector<double> values = lo->getValuesVector();

  // for (int i = topIndex; i < bottomIndex; ++i)
  // polygon.append(QPointF(values[i], lo->getTopDepth() + i * lo->getStep()));

  // painter.drawPolyline(polygon);

  // QTransform t = painter.transform();

  // pen.setStyle(Qt::SolidLine);
  // pen.setColor(Qt::black);
  // painter.setBrush(Qt::yellow);
  // painter.setPen(pen);

  // it.toFront();
  // while(it.hasNext())
  // {
  // if (it.peekNext().y() <
  // qMax(_controller->parent()->topDepth(),
  // rect.top())) {
  // it.next();
  // continue;
  // }
  // if (it.peekNext().y() >
  // qMin(_controller->parent()->bottomDepth(),
  // rect.bottom())) {
  // break;
  // }

  // painter.save();
  // painter.resetTransform();
  // QPointF p = t.map(it.peekNext());
  // painter.translate(p);
  // painter.drawEllipse(QPointF(0.0, 0.0), 3.0, 3.0);

  // painter.restore();

  // it.next();
  // }
}


void
ContinuousCurveView::
paintBodyLog10(QPainter&                painter,
               Scalers::Scaler::Pointer scaler,
               QRectF&                  rect)
{
  Q_UNUSED(scaler);

  // QPen pen;
  // pen.setWidthF(_curve->getThickness());
  // pen.setColor(_curve->getColor());
  // pen.setCosmetic(true);
  //// pen.setStyle(_lineStyle);

  // painter.setRenderHint(QPainter::Antialiasing);

  // painter.setPen(pen);

  // const SectionControllers::LogarithmicGridController* const
  // logarithmicGridController =
  // static_cast<const SectionControllers::
  // LogarithmicGridController*>(
  // _controller->parent());
  // painter.scale(_controller->parent()->width() /
  // (logarithmicGridController->maxLog10Value() -
  // logarithmicGridController->minLog10Value()), 1.0);

  // painter.translate(-logarithmicGridController->minLog10Value(),
  // 0.0);

  // QListIterator<QPointF> it(_curveLog10Data);

  // it.next();

  // while (it.hasPrevious() && it.hasNext()) {
  // if (it.peekNext().y() <
  // qMax(_controller->parent()->topDepth(), rect.top())) {
  // it.next();
  // continue;
  // }

  // if (it.peekPrevious().y() >
  // qMin(_controller->parent()->bottomDepth(), rect.bottom()))
  // break;

  // painter.drawLine(it.peekPrevious(), it.peekNext());

  // it.next();
  // }
}


void
ContinuousCurveView::
postOffsetPainterForHeader(QPainter& painter)
{
  painter.translate(0.0, 0.01);
}


void
ContinuousCurveView::
postOffsetPainterForBody(QPainter& painter)
{
  Q_UNUSED(painter);
}
}
}
}
