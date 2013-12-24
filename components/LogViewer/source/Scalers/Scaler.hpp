#ifndef Geo_Logviwer_Scalers_Scaler_hpp
#define Geo_Logviwer_Scalers_Scaler_hpp

#include <QObject>
#include <QPoint>
#include <QSharedPointer>
#include <QTransform>

#include "AxisScaler.hpp"

namespace Geo {
namespace LogViewer {
namespace Scalers {
class QPaintDevice;

class Scaler : public QObject {
  Q_OBJECT

public:
  typedef QSharedPointer<Scaler> Pointer;
  /** Constructor
   * Default arguments - 1:1 cm in x direction
   * and 200 cm : 1 cm in y diretion
   */
  Scaler(AxisScaler::Pointer xScaler,
         AxisScaler::Pointer yScaler);

  virtual
  ~Scaler() {}

  /** takes QPoint - position of some point on GLWidget
   * @returns QPointF - position on LogView (both directions in meters)
   */
  virtual QPointF
  mapPixelsToLogView(QPoint& p);

  virtual QPoint
  mapLogViewToPixels(QPointF& p);

  virtual QSizeF
  scalePixelsToLogView(QSize& s);

  virtual QSize
  scaleLogViewToPixels(QSizeF& s);

  /** Here we use xscale_ and yscale_ variables
   * Takes real coordinates and multiplies them by scale factors
   */
  virtual QPointF
  mapRealCoordsToLogView(QPointF p);

  /// Here we use xscale_ and yscale_ variables
  virtual QPointF
  mapLogViewToRealCoords(QPointF& p);

  virtual QPoint
  mapRealCoordsToPixels(QPointF& p);

  virtual QPointF
  mapPixelsToRealCoords(QPoint p);

  /** Transformation is used to shift and scale coordinate system
   * of painting widget to draw all the objects in their own coordinates
   * i.e. draw point at (15.5 cm, 2024.0 m) instead of (663 px, 788 px)
   */
  QTransform
  getTransform();

  void
  multiplyXScale(double multiplier);

  void
  multiplyYScale(double multiplier);

  void
  setXScale(double xscale);

  void
  setYScale(double yscale);

  double
  xScale();

  double
  yScale();

  AxisScaler::Pointer
  xScaler();

  AxisScaler::Pointer
  yScaler();

  void
  setXOffset(int xoffset);

  void
  setYOffset(int yoffset);

  int
  xOffset();

  int
  yOffset();

  void
  addToOffset(QPoint p);

  void
  addToXOffset(int dx);

  void
  addToYOffset(int dy);

signals:
  void
  xScaleChanged();

  void
  yScaleChanged();

protected:
  /** number of cm of well in 1 cm of screen
   * WellDepth/ScreenSize
   * scale between meters
   */
  AxisScaler::Pointer _xScaler;
  AxisScaler::Pointer _yScaler;
};
}
}
}

#endif // Geo_Logviwer_Scalers_Scaler_hpp
