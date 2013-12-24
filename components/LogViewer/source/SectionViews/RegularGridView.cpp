#include "RegularGridView"

#include <QPainter>

#include "../SectionControllers/AbstractSectionController.hpp"

#include "ContinuousCurveView.hpp"
#include "WellView.hpp"

namespace Geo {
namespace LogViewer {
namespace SectionViews {
RegularGridView::
RegularGridView(
  SectionControllers::AbstractSectionController* controller,
  Domain::Grid::Pointer                          grid)
  : AbstractGridView(controller),
    _grid(grid)
{}

void
RegularGridView::
paintHeader(QPainter&                painter,
            Scalers::Scaler::Pointer scaler,
            QRectF&                  rect) {
  Q_UNUSED(scaler);

  painter.setPen(Qt::black);
  painter.setBrush(Qt::white);
  painter.drawRect(QRectF(0.0, 0.0, _controller->width(), rect.height()));
}

void
RegularGridView::
paintBody(QPainter&                painter,
          Scalers::Scaler::Pointer scaler,
          QRectF&                  rect) {
  QPointF
    gridSmallStepLogView(0.005, 0.005);

  QPointF
    gridStepLogView(0.02, 0.02);

  QPointF gridSmallStepReal = scaler->mapLogViewToRealCoords(
    gridSmallStepLogView);
  QPointF gridStepReal = scaler->mapLogViewToRealCoords(gridStepLogView);

  double offset = 0.0;

  QPen pen;
  pen.setStyle(Qt::DashLine);
  pen.setColor(_grid->getColor());
  painter.setPen(pen);

  // small steps

  double top = qMax(rect.top(), _controller->parent()->topDepth());

  while (offset <= _controller->width()) {
    painter.drawLine(QPointF(offset, top),
                     QPointF(offset,
                             qMin(rect.bottom(),
                                  _controller->parent()->bottomDepth())));
    offset += gridSmallStepReal.x();
  }

  int d =
    int((qMax(rect.top(),
              _controller->parent()->topDepth()) -
         _controller->parent()->parent()->topDepth()) / gridSmallStepReal.y());
  offset = _controller->parent()->parent()->topDepth() +
           (d + 1) * gridSmallStepReal.y();

  while (offset <=
                             qMin(rect.bottom(),
              _controller->parent()->bottomDepth())) {
    painter.drawLine(QPointF(0.0, offset),
                     QPointF(_controller->width(), offset));
    offset += gridSmallStepReal.y();
  }

  // large steps
  pen.setStyle(Qt::SolidLine);
  pen.setColor(_grid->getColor());
  painter.setPen(pen);

  offset = 0.0;

  while (offset <= _controller->width()) {
    painter.drawLine(QPointF(offset, top),
                     QPointF(offset,
                             qMin(rect.bottom(),
                                  _controller->parent()->bottomDepth())));
    offset += gridStepReal.x();
  }

  painter.drawLine(QPointF(_controller->width(), top),
                   QPointF(_controller->width(),
                           qMin(rect.bottom(),
                                _controller->parent()->bottomDepth())));

  d =
    int((qMax(rect.top(),
              _controller->parent()->topDepth()) -
         _controller->parent()->parent()->topDepth()) / gridStepReal.y());
  offset = _controller->parent()->parent()->topDepth() +
           (d + 1) * gridStepReal.y();

  while (offset <=
                           qMin(rect.bottom(),
              _controller->parent()->bottomDepth())) {
    painter.drawLine(QPointF(0.0, offset),
                     QPointF(_controller->width(), offset));
    offset += gridStepReal.y();
  }
}

void
RegularGridView::
postOffsetPainterForHeader(QPainter& painter) {
  painter.translate(_controller->width(), 0.0);
}

void
RegularGridView::
postOffsetPainterForBody(QPainter& painter) {
  painter.translate(_controller->width(), 0.0);
}
}
}
}
