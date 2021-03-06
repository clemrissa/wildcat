#ifndef Geo_LogViewer_SectionViews_LogarithmicGridView_hpp
#define Geo_LogViewer_SectionViews_LogarithmicGridView_hpp

// #include <Geo/Domain/Grid>

#include "AbstractGridView.hpp"

#include "../Scalers/Scaler.hpp"

namespace Geo {
namespace LogViewer {
namespace SectionViews {
class LogarithmicGridView: public AbstractGridView {
public:
  LogarithmicGridView(SectionControllers::AbstractSectionController* controller);
  // Domain::Grid::Pointer                          grid);

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

  // private:
  // Domain::Grid::Pointer _grid;
};
}
}
}

#endif // Geo_LogViewer_SectionViews_LogarithmicGridView_hpp
