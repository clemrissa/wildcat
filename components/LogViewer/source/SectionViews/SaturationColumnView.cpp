#include "SaturationColumnView"

#include <QPainter>

#include "../SectionControllers/AbstractSectionController"

#include "WellView"

namespace Geo {
namespace LogViewer {
namespace SectionViews {
SaturationColumnView::
SaturationColumnView(
  SectionControllers::AbstractSectionController* controller):
  AbstractSectionView(controller) {}

void
SaturationColumnView::
paintHeader(QPainter&                painter,
            Scalers::Scaler::Pointer scaler,
            QRectF&                  rect) {
  Q_UNUSED(painter);
  Q_UNUSED(scaler);
  Q_UNUSED(rect)
}

void
SaturationColumnView::
paintBody(QPainter&                painter,
          Scalers::Scaler::Pointer scaler,
          QRectF&                  rect) {
  Q_UNUSED(rect);
  Q_UNUSED(scaler);

  QPen pen(Qt::SolidLine);

  pen.setColor(_color);
  pen.setCosmetic(true);
  painter.setPen(pen);

  QListIterator<QPointF> it(_columnData);

  it.next();

  // it is hard to imagine a more disgusting color
  QImage image(":/BMP/Color/Char/2c.bmp");

  image = image.scaledToHeight(24, Qt::SmoothTransformation);
  QMatrix m = painter.matrix().inverted();
  m.translate(painter.matrix().dx(),
              painter.matrix().dy());
  QBrush brush(image);

  brush.setMatrix(m);

  while (it.hasPrevious() && it.hasNext()) {
    if (it.peekNext().x() > 0.0) {
      QRectF rect(0.0, it.peekPrevious().y(), _controller->width(),
                  it.peekNext().y() - it.peekPrevious().y());

      painter.drawRect(rect);
      painter.fillRect(rect, brush);
    }

    it.next();
  }
}
}
}
}
