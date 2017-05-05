#include "Scaler.hpp"

#include <QPaintDevice>
#include <QProcess>

#include "AxisScaler.hpp"

namespace Geo {
namespace LogViewer {
namespace Scalers {
Scaler::
Scaler(AxisScaler::Pointer xScaler,
       AxisScaler::Pointer yScaler):
  _xScaler(xScaler),
  _yScaler(yScaler) {
  //
}

QPointF
Scaler::
mapPixelsToLogView(QPoint& p) {
  return QPoint(_xScaler->mapPixelsToLogView(p.x()),
                _yScaler->mapPixelsToLogView(p.y()));
}

QPoint
Scaler::
mapLogViewToPixels(QPointF& p) {
  return QPoint(_xScaler->mapLogViewToPixels(p.x()),
                _xScaler->mapLogViewToPixels(p.x()));
}

QSizeF
Scaler::
scalePixelsToLogView(QSize& s) {
  return QSizeF(_xScaler->scalePixelsToLogView(s.width()),
                _yScaler->scalePixelsToLogView(s.height()));
}

QSize
Scaler::
scaleLogViewToPixels(QSizeF& s) {
  return QSize(_xScaler->scaleLogViewToPixels(s.width()),
               _yScaler->scaleLogViewToPixels(s.height()));
}

/// Here we use xscale_ and yscale_ variables
QPointF
Scaler::
mapRealCoordsToLogView(QPointF p) {
  /// scale = real / logView
  return QPointF(_xScaler->mapRealCoordsToLogView(p.x()),
                 _yScaler->mapRealCoordsToLogView(p.y()));
}

/// Here we use xscale_ and yscale_ variables
QPointF
Scaler::
mapLogViewToRealCoords(QPointF& p) {
  return QPointF(_xScaler->mapLogViewToRealCoords(p.x()),
                 _yScaler->mapLogViewToRealCoords(p.y()));
}

QPoint
Scaler::
mapRealCoordsToPixels(QPointF& p) {
  return QPoint(_xScaler->mapRealCoordsToPixels(p.x()),
                _yScaler->mapRealCoordsToPixels(p.y()));
}

QPointF
Scaler::
mapPixelsToRealCoords(QPoint p) {
  return QPointF(_xScaler->mapPixelsToRealCoords(p.x()),
                 _yScaler->mapPixelsToRealCoords(p.y()));
}

QTransform
Scaler::
getTransform() {
  QTransform t;

  t.translate(_xScaler->getOffset(),
              _yScaler->getOffset());

  t.scale(1.0 * _xScaler->getScale(),
          1.0 * _yScaler->getScale());

  double dotsPerMeter = xScaler()->getDotsPerMeter();
  t.scale(dotsPerMeter, dotsPerMeter);

  return t;
}

void
Scaler::
multiplyXScale(double multiplier) {
  _xScaler->multiplyScale(multiplier);
  emit
    xScaleChanged();
}

void
Scaler::
multiplyYScale(double multiplier) {
  _yScaler->multiplyScale(multiplier);
  emit
    yScaleChanged();
}

void
Scaler::
setXScale(double xscale) {
  _xScaler->setScale(xscale);
  emit
    xScaleChanged();
}

void
Scaler::
setYScale(double yscale) {
  _yScaler->setScale(yscale);
  emit
    yScaleChanged();
}

double
Scaler::
xScale() {
  return _xScaler->getScale();
}

double
Scaler::
yScale() {
  return _yScaler->getScale();
}

AxisScaler::Pointer
Scaler::
xScaler() {
  return _xScaler;
}

AxisScaler::Pointer
Scaler::
yScaler() {
  return _yScaler;
}

void
Scaler::
addToOffset(QPoint p) {
  _xScaler->addToOffset(p.x());
  _yScaler->addToOffset(p.y());
}

void
Scaler::
addToXOffset(int dx) {
  _xScaler->addToOffset(dx);
  // correctOffsets();
}

void
Scaler::
addToYOffset(int dy) {
  _yScaler->addToOffset(dy);
  // correctOffsets();
}

void
Scaler::
setXOffset(int xoffset) {
  _xScaler->setOffset(xoffset);
  // correctOffsets();
}

void
Scaler::
setYOffset(int yoffset) {
  _yScaler->setOffset(yoffset);
  // correctOffsets();
}

int
Scaler::
xOffset() {
  return _xScaler->getOffset();
}

int
Scaler::
yOffset() {
  return _yScaler->getOffset();
}
}
}
}
