#ifndef Geo_LogViewer_SectionViews_ContinuousCurveView_hpp
#define Geo_LogViewer_SectionViews_ContinuousCurveView_hpp

#include <Geo/Domain/Curve>

#include "AbstractGridView"

namespace Geo {
namespace LogViewer {
namespace SectionViews {
class ContinuousCurveView: public AbstractSectionView {
public:
  ContinuousCurveView(
    SectionControllers::AbstractSectionController* controller,
    Domain::Curve::Pointer                         curve);

public:
  void
  paintHeader(QPainter&                painter,
              Scalers::Scaler::Pointer scaler,
              QRectF&                  rect);

  void
  paintHeaderLog10(QPainter&                painter,
                   Scalers::Scaler::Pointer scaler,
                   QRectF&                  rect);

  void
  paintBody(QPainter&                painter,
            Scalers::Scaler::Pointer scaler,
            QRectF&                  rect);

  void
  paintBodyLog10(QPainter&                painter,
                 Scalers::Scaler::Pointer scaler,
                 QRectF&                  rect);

  void
  postOffsetPainterForHeader(QPainter& painter) override;

  void
  postOffsetPainterForBody(QPainter& painter) override;

private:
  Domain::Curve::Pointer _curve;

  QList<QPointF> _curveData;
  QList<QPointF> _curveLog10Data;

  double _minLog10Value;
  double _maxLog10Value;
};
}
}
}

#endif // Geo_LogViewer_SectionViews_ContinuousCurveView_hpp
