#ifndef Geo_Logviwer_SectionViews_WellView_hpp
#define Geo_Logviwer_SectionViews_WellView_hpp

// #include <Geo/Domain/VisualWell>

#include "AbstractSectionView.hpp"

namespace Geo {
namespace LogViewer {
namespace SectionControllers {
class AbstractSectionController;
}

namespace Scalers {
class Scaler;
}

namespace SectionViews {
class WellView: public AbstractSectionView {
public:
  WellView(SectionControllers::AbstractSectionController* controller);
  // Domain::VisualWell::Pointer                    visualWell);

  virtual
  ~WellView() {}

  virtual void
  paintHeader(QPainter&                painter,
              Scalers::Scaler::Pointer scaler,
              QRectF&                  rect);

  virtual void
  paintBody(QPainter&                painter,
            Scalers::Scaler::Pointer scaler,
            QRectF&                  rect);

  void
  preOffsetPainterForHeader(QPainter& painter) override;

  void
  postOffsetPainterForHeader(QPainter& painter) override;

  void
  postOffsetPainterForBody(QPainter& painter) override;

  // private:
  // Domain::VisualWell::Pointer _visualWell;
};
}
}
}

#endif // Geo_Logviwer_SectionViews_WellView_hpp
