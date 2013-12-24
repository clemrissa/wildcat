#ifndef Geo_LogViewer_SectionViews_DepthColumnView_hpp
#define Geo_LogViewer_SectionViews_DepthColumnView_hpp

#include "AbstractSectionView"

namespace Geo {
namespace LogViewer {
namespace SectionViews {
class DepthColumnView: public AbstractSectionView {
public:
  DepthColumnView(
    SectionControllers::AbstractSectionController* controller);

public:
  void
  paintHeader(QPainter&                painter,
              Scalers::Scaler::Pointer scaler,
              QRectF&                  rect);

  void
  paintBody(QPainter&                painter,
            Scalers::Scaler::Pointer scaler,
            QRectF&                  rect);

  void
  postOffsetPainterForHeader(QPainter& painter) override;

  void
  postOffsetPainterForBody(QPainter& painter) override;
};
}
}
}

#endif // Geo_LogViewer_SectionViews_DepthColumnView_hpp
