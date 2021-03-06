#ifndef Geo_Logviwer_Scalers_AxisScaler_hpp
#define Geo_Logviwer_Scalers_AxisScaler_hpp

#include <QObject>
#include <QSharedPointer>
#include <QTransform>

class QPaintDevice;

namespace Geo {
namespace LogViewer {
namespace Scalers {
class AxisScaler : public QObject {
  Q_OBJECT

public:
  typedef QSharedPointer<AxisScaler> Pointer;

  /** Constructor
   * Default arguments - 1:1 cm in x direction
   * and 200 cm : 1 cm in y diretion
   */
  AxisScaler(double dostPerInch, double scale = 1 / 2.0);

  virtual
  ~AxisScaler() {}

  /**
   * takes QPoint - position of some point on GLWidget
   * @returns QPointF - position on LogView (both directions in meters)
   */
  virtual double
  mapPixelsToLogView(int p);

  virtual int
  mapLogViewToPixels(double p);

  virtual double
  scalePixelsToLogView(int p);

  virtual int
  scaleLogViewToPixels(double p);

  /// Here we use scale_
  virtual double
  mapRealCoordsToLogView(double p);

  /// Here we use xscale_ and yscale_ variables
  virtual double
  mapLogViewToRealCoords(double p);

  /// Maps real-world cooridnates to pixels
  virtual int
  mapRealCoordsToPixels(double p);

  // maps pixels to real-world coordinates
  virtual double
  mapPixelsToRealCoords(int p);

  /// Maps real-world cooridnates to pixels
  virtual int
  scaleRealCoordsToPixels(double p);

  // maps pixels to real-world coordinates
  virtual double
  scalePixelsToRealCoords(int p);

  void
  multiplyScale(double multiplier);
  void
  setScale(double scale);
  double
  getScale() { return _scale; }

  void
  addToOffset(int p);
  void
  setOffset(int offset);
  int
  getOffset() { return _pixelOffset; }

  double
  getDotsPerMeter() { return _dotsPerMeter; }

signals:
  void
  scalerChanged();

protected:
  /** number of cm of well in 1 cm of screen
   *  WellDepth/ScreenSize
   *  scale between meters
   */
  double _scale;

  /** offset of logView relative to (0,0) corner of widget
   * measured in Pixels
   */
  int _pixelOffset;

  /** offset in real coordinates.
   * for example when well starts at 300 meters (not 0.0)
   */
  double _realOffset;

  /** Is used for pixel -> meters conversion
   */
  double _dotsPerMeter;
};
}
}
}

#endif // Geo_Logviwer_Scalers_AxisScaler_hpp
