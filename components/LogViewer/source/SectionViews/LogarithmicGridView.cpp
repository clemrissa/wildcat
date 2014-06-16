#include "LogarithmicGridView.hpp"

#include <QPainter>

#include <math.h>

#include "../SectionControllers/LogarithmicGridController.hpp"

#include "../Scalers/Scaler.hpp"
#include "ContinuousCurveView.hpp"
#include "WellView.hpp"

namespace Geo {
namespace LogViewer {
namespace SectionViews {
LogarithmicGridView::
LogarithmicGridView(
  SectionControllers::AbstractSectionController* controller):
  // Domain::Grid::Pointer                          grid):
  AbstractGridView(controller)

  // _grid(grid)
{}

void
LogarithmicGridView::
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
LogarithmicGridView::
paintBody(QPainter&                painter,
          Scalers::Scaler::Pointer scaler,
          QRectF&                  rect)
{
  SectionControllers::LogarithmicGridController* logController =
    static_cast<SectionControllers::LogarithmicGridController*>(_controller);

  double gridLargeYStepReal = scaler->yScaler()->mapLogViewToRealCoords(0.02);
  double gridLargeXStepReal = logController->width() /
                              (logController->maxLog10Value() -
                               logController->minLog10Value());
  double gridSmallYStepReal = scaler->yScaler()->mapLogViewToRealCoords(0.005);

  // small steps -------------------------

  painter.save();
  {
    QPen
      pen(Qt::DashLine);

    pen.setColor(QColor(Qt::gray).lighter(150));
    painter.setPen(pen);

    // vertical ------

    double top  = qMax(rect.top(), _controller->parent()->topDepth());
    double left =
      (floor(logController->minLog10Value()) -
       logController->minLog10Value()) * gridLargeXStepReal;

    int    logStep = 2.0;
    double dx      =
      (log10(logStep) - log10(logStep - 1)) * gridLargeXStepReal;
    double offset = left + dx;

    while (offset < _controller->width()) {
      if (offset > 0.0)
        painter.drawLine(QPointF(offset, top),
                         QPointF(offset,
                                 qMin(rect.bottom(),
                                      _controller->bottomDepth())));

      logStep += 1.0;

      if (logStep > 10.0)
        logStep = 2.0;

      dx = (log10(logStep) - log10(logStep - 1)) * gridLargeXStepReal;

      offset += dx;
    }

    // horizontal ------

    int d =
      int((qMax(rect.top(),
                _controller->topDepth()) -
           _controller->parent()->parent()->topDepth()) / gridSmallYStepReal);
    offset = _controller->parent()->parent()->topDepth() +
             (d + 1) * gridSmallYStepReal;

    while (offset <=
           qMin(rect.bottom(),
                _controller->parent()->bottomDepth())) {
      painter.drawLine(QPointF(0.0, offset),
                       QPointF(_controller->width(), offset));
      offset += gridSmallYStepReal;
    }
  }
  painter.restore();

  // large steps -------------------------

  double offset =
    (ceil(logController->minLog10Value()) -
     logController->minLog10Value()) * gridLargeXStepReal;
  painter.save();
  {
    // vertical ------

    QPen
      pen(Qt::SolidLine);

    pen.setColor(QColor(Qt::blue).lighter(180));
    painter.setPen(pen);
    double top = qMax(rect.top(), _controller->parent()->topDepth());

    while (offset < _controller->width()) {
      painter.drawLine(QPointF(offset, top),
                       QPointF(offset,
                               qMin(rect.bottom(),
                                    _controller->parent()->bottomDepth())));
      offset += gridLargeXStepReal;
    }

    painter.drawLine(QPointF(_controller->width(), top),
                     QPointF(_controller->width(),
                             qMin(rect.bottom(),
                                  _controller->parent()->bottomDepth())));

    // horizontal ------

    double d =
      int((qMax(rect.top(),
                _controller->parent()->topDepth()) -
           _controller->parent()->parent()->topDepth()) / gridLargeYStepReal);
    offset = _controller->parent()->parent()->topDepth() +
             (d + 1) * gridLargeYStepReal;

    while (offset <=
           qMin(rect.bottom(),
                _controller->parent()->bottomDepth())) {
      painter.drawLine(QPointF(0.0, offset),
                       QPointF(_controller->width(), offset));
      offset += gridLargeYStepReal;
    }
  }
  painter.restore();
}


void
LogarithmicGridView::
postOffsetPainterForHeader(QPainter& painter)
{
  painter.translate(_controller->width(), 0.0);
}


void
LogarithmicGridView::
postOffsetPainterForBody(QPainter& painter)
{
  painter.translate(_controller->width(), 0.0);
}
}
}
}
