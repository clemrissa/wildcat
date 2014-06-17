#include "WellView.hpp"

#include <QDebug>
#include <QPainter>
#include <QTime>

#include "DepthColumnView.hpp"
#include "LogarithmicGridView.hpp"
#include "RegularGridView.hpp"
#include "SaturationColumnView.hpp"

#include "../SectionControllers/AbstractSectionController.hpp"

using Geo::LogViewer::SectionViews::WellView;

WellView::
WellView(SectionControllers::AbstractSectionController* controller):
  // Domain::VisualWell::Pointer                    visualWell):
  AbstractSectionView(controller)
  // _visualWell(visualWell)
{}

void
WellView::
paintHeader(QPainter&                painter,
            Scalers::Scaler::Pointer scaler,
            QRectF&                  rect)
{
  Q_UNUSED(scaler);

  painter.setPen(Qt::black);
  painter.setBrush(Qt::white);

  painter.drawRect(QRectF(0.0, 0.0, _controller->width(), rect.height()));

  // Paint Well Name on top of header
  {
    QFont font("Monospace");

    font.setStyleHint(QFont::TypeWriter);
    font.setPixelSize(16);
    painter.setFont(font);
    painter.setPen(QColor(Qt::gray).darker());
    // now paint text
    QTransform t = painter.transform();
    painter.save();
    {
      painter.resetTransform();

      const QString name("Well Name");

      QFontMetrics metrics = painter.fontMetrics();

      double w =
        scaler->xScaler()->scalePixelsToRealCoords(metrics.width(name));

      QPointF p = t.map(QPointF((_controller->width() - w) / 2.0,
                                0.0085));
      painter.translate(p);
      painter.drawText(0.0, 0.0, name);
    }
    painter.restore();
  }
}


void
WellView::
paintBody(QPainter&                painter,
          Scalers::Scaler::Pointer scaler,
          QRectF&                  rect)
{
  Q_UNUSED(scaler);
  Q_UNUSED(rect);

  painter.setPen(Qt::black);
  painter.setBrush(Qt::white);
  painter.drawRect(QRectF(0.0, _controller->topDepth(), _controller->width(),
                          _controller->height()));
}


void
WellView::
preOffsetPainterForHeader(QPainter& painter)
{
  painter.translate(0.0, 0.01);
}


void
WellView::
postOffsetPainterForHeader(QPainter& painter)
{
  const double wellOffset = 0.01;
  painter.translate(_controller->width() + wellOffset, 0.0);
}


void
WellView::
postOffsetPainterForBody(QPainter& painter)
{
  const double wellOffset = 0.01;
  painter.translate(_controller->width() + wellOffset, 0.0);
}
