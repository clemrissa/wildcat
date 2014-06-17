#ifndef Geo_LogViewer_SectionViews_MultiWellSection_hpp
#define Geo_LogViewer_SectionViews_MultiWellSection_hpp

// #include <Geo/Domain/LogView>

#include "AbstractSectionView.hpp"

#include "../Scalers/Scaler.hpp"

namespace Geo {
namespace LogViewer {
namespace SectionControllers {
class AbstractSectionController;
}

namespace SectionViews {
class MultiWellSectionView: public AbstractSectionView {
public:
  typedef QScopedPointer<MultiWellSectionView> Pointer;

  MultiWellSectionView(SectionControllers::AbstractSectionController*
                       controller);
  // Domain::LogView::Pointer                       logView);

  virtual
  ~MultiWellSectionView() {}

  void
  paintHeader(QPainter&                painter,
              Scalers::Scaler::Pointer scaler,
              QRectF&                  r) override;

  void
  paintBody(QPainter&                painter,
            Scalers::Scaler::Pointer scaler,
            QRectF&                  r) override;

  // private:
  // Domain::LogView::Pointer _logView;
};
}
}
}

#endif // Geo_LogViewer_SectionViews_MultiWellSection_hpp
