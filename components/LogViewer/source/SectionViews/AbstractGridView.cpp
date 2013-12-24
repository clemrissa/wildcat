#include "AbstractGridView"

#include "WellView.hpp"

namespace Geo {
namespace LogViewer {
namespace SectionViews {
AbstractGridView::
AbstractGridView(
  SectionControllers::AbstractSectionController* controller)
  : AbstractSectionView(controller)
{}
}
}
}
