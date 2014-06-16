#include "DepthColumnView.hpp"

#include <QPainter>

#include "../SectionControllers/AbstractSectionController.hpp"

#include "WellView.hpp"

namespace Geo {
namespace LogViewer {
namespace SectionViews {
DepthColumnView::
DepthColumnView(
  SectionControllers::AbstractSectionController* controller):
  AbstractSectionView(controller) {}

void
DepthColumnView::
paintHeader(QPainter&                painter,
            Scalers::Scaler::Pointer scaler,
            QRectF&                  rect)
{
  Q_UNUSED(scaler);

  painter.setPen(Qt::black);
  painter.setBrush(Qt::white);
  painter.drawRect(QRectF(0.0, 0.0, _controller->width(), rect.height()));
}


void
DepthColumnView::
paintBody(QPainter&                painter,
          Scalers::Scaler::Pointer scaler,
          QRectF&                  rect)
{
  double gridSmallStepLogView = 0.005;
  double gridStepLogView      = 0.02;

  double gridSmallStepReal = scaler->yScaler()->mapLogViewToRealCoords(
    gridSmallStepLogView);
  double gridStepReal = scaler->yScaler()->mapLogViewToRealCoords(
    gridStepLogView);

  double offset = 0.0;

  QPen pen;
  pen.setColor(QColor(Qt::gray).lighter(150));
  painter.setPen(pen);

  int d =
    int((qMax(rect.top(),
              _controller->parent()->topDepth()) -
         _controller->parent()->parent()->topDepth()) / gridSmallStepReal);
  offset = _controller->parent()->parent()->topDepth() +
           (d + 1) * gridSmallStepReal;

  while (offset <=
         qMin(rect.bottom(), _controller->parent()->bottomDepth())) {
    painter.drawLine(QPointF(0.0, offset),
                     QPointF(_controller->width(), offset));
    offset += gridSmallStepReal;
  }

  // ===========
  // large steps
  painter.setPen(QColor(Qt::gray).lighter(130));

  d =
    int((qMax(rect.top(),
              _controller->parent()->topDepth()) -
         _controller->parent()->parent()->topDepth()) / gridStepReal);
  offset = _controller->parent()->parent()->topDepth() +
           (d + 1) * gridStepReal;

  while (offset <=
         qMin(rect.bottom(), _controller->parent()->bottomDepth())) {
    painter.drawLine(QPointF(0.0, offset),
                     QPointF(_controller->width(), offset));
    offset += gridStepReal;
  }

  painter.setPen(QColor(Qt::gray).darker());

  QFont
    font("Monospace");

  font.setStyleHint(QFont::TypeWriter);
  font.setPixelSize(10);

  painter.setFont(font);

  offset = _controller->parent()->parent()->topDepth() +
           (d + 1) * gridStepReal;
  QTransform t = painter.transform();

  while (offset <=
         qMin(rect.bottom(), _controller->parent()->bottomDepth())) {
    painter.save();
    painter.resetTransform();
    QPointF p = t.map(QPointF(0.0, offset));
    painter.translate(p);
    painter.drawText(2, -1, QString::number(offset, 'f', 2));
    painter.restore();

    offset += gridStepReal;
  }
}


void
DepthColumnView::
postOffsetPainterForHeader(QPainter& painter)
{
  painter.translate(_controller->width(), 0.0);
}


void
DepthColumnView::
postOffsetPainterForBody(QPainter& painter)
{
  painter.translate(_controller->width(), 0.0);
}
}
}
}
