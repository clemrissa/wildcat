#ifndef Geo_LogViewer_SectionViews_AbstractGridView_hpp
#define Geo_LogViewer_SectionViews_AbstractGridView_hpp

#include <QColor>

#include "AbstractSectionView"

namespace Geo {
namespace LogViewer {
namespace SectionViews {
class AbstractGridView: public AbstractSectionView {
public:
  AbstractGridView(
    SectionControllers::AbstractSectionController* controller);

  bool
  hasDepthLimits() { return true; }
};
}
}
}

#endif // Geo_LogViewer_SectionViews_AbstractGridView_hpp
