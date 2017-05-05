#include "AxisScaler.hpp"

#include <QPaintDevice>
#include <QProcess>
#include <QTransform>

namespace Geo {
namespace LogViewer {
namespace Scalers {
AxisScaler::
AxisScaler(double dotsPerInch, double scale)
  : _scale(scale),
    _pixelOffset(0),
    _realOffset(0.0) {
  _dotsPerMeter =  dotsPerInch / (2.540 * 0.01);
}

double
AxisScaler::
mapPixelsToLogView(int p) {
  p -= _pixelOffset;

  return scalePixelsToLogView(p);
}

int
AxisScaler::
mapLogViewToPixels(double p) {
  // double dotsPerMeter = pixels / meters

  int pixelsPos = scaleLogViewToPixels(p);

  pixelsPos += int(_pixelOffset);

  return pixelsPos;
}

double
AxisScaler::
scalePixelsToLogView(int p) {
  return p / _dotsPerMeter;
}

int
AxisScaler::
scaleLogViewToPixels(double p) {
  return p * _dotsPerMeter;
}

/// Here we use _scale and y_scale variables
double
AxisScaler::
mapRealCoordsToLogView(double p) {
  /// scale = real / logView
  return p * _scale;
}

/// Here we use _scale and y_scale variables
double
AxisScaler::
mapLogViewToRealCoords(double p) {
  return double(p / _scale);
}

int
AxisScaler::
mapRealCoordsToPixels(double p) {
  return mapLogViewToPixels(mapRealCoordsToLogView(p));
}

double
AxisScaler::
mapPixelsToRealCoords(int p) {
  return mapLogViewToRealCoords(mapPixelsToLogView(p));
}

int
AxisScaler::
scaleRealCoordsToPixels(double p) {
  return scaleLogViewToPixels(mapRealCoordsToLogView(p));
}

double
AxisScaler::
scalePixelsToRealCoords(int p) {
  return mapLogViewToRealCoords(scalePixelsToLogView(p));
}

// ------------------------------------------------------------------------------

void
AxisScaler::
multiplyScale(double multiplier) {
  _scale *= multiplier;

  if (_scale > 5) {
    _scale = 5;

    return;
  }

  emit
    scalerChanged();
}

void
AxisScaler::
setScale(double scale) {
  _scale = scale;

  if (_scale > 5) {
    _scale = 5;

    return;
  }

  emit
    scalerChanged();
}

void
AxisScaler::
addToOffset(int p) {
  _pixelOffset += p;
  emit
    scalerChanged();
}

void
AxisScaler::
setOffset(int offset) {
  _pixelOffset = offset;
  emit
    scalerChanged();
}
}
}
}
