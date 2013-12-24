#include "SaturationColumnController"

#include <QPainter>

#include "WellController"

namespace Geo {
namespace LogViewer {
namespace SectionControllers {
SaturationColumnController::
SaturationColumnController(AbstractSectionController* well):
  AbstractSectionController(well),
  _color(QColor(Qt::gray)) {
  double step = 10.; // meters

  _topDepth    = 100 + qrand() % 300;
  _bottomDepth = 600 + qrand() % 200;

  double depth     = topDepth();
  double lastDepth = depth - step;

  _columnData.append(QPointF(0.0, lastDepth));

  while (depth < bottomDepth()) {
    int    r1    = qrand() % 10;
    double value = 0.0;

    if (r1 > 5)
      value = 10.0;

    _columnData.append(QPointF(value, depth));

    depth += step;
  }

  recalculateSize();
}

double
SaturationColumnController::
topDepth() const {
  return _topDepth;
}

double
SaturationColumnController::
bottomDepth() const {
  return _bottomDepth;
}

double
SaturationColumnController::
width() const {
  return _width;
}

void
SaturationColumnController::
paintHeader(QPainter&                painter,
            Scalers::Scaler::Pointer scaler,
            QRectF&                  rect) {
  Q_UNUSED(painter);
  Q_UNUSED(scaler);
  Q_UNUSED(rect)
}

void
SaturationColumnController::
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
      QRectF rect(0.0, it.peekPrevious().y(), _width,
                  it.peekNext().y() - it.peekPrevious().y());

      painter.drawRect(rect);
      painter.fillRect(rect, brush);
    }

    it.next();
  }
}

void
SaturationColumnController::
recalculateWidth() {
  _width = 0.015; // m
}
}
}
}
