#ifndef Geo_LogViewer_SectionViews_SaturationColumnView_hpp
#define Geo_LogViewer_SectionViews_SaturationColumnView_hpp

#include <QColor>

#include "AbstractSectionView.hpp"

namespace Geo {
namespace LogViewer {
namespace SectionControllers {
class AbstractSectionController;
}

namespace SectionViews {
class WellView;

class SaturationColumnView: public AbstractSectionView {
public:
  SaturationColumnView(
    SectionControllers::AbstractSectionController* controller);

  void
  paintHeader(QPainter&                painter,
              Scalers::Scaler::Pointer scaler,
              QRectF&                  rect);

  void
  paintBody(QPainter&                painter,
            Scalers::Scaler::Pointer scaler,
            QRectF&                  rect);

protected:
  QColor         _color;
  QList<QPointF> _columnData;
};
}
}
}

#endif // Geo_LogViewer_SectionViews_SaturationColumnView_hpp
