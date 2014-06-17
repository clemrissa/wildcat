#include "GenericRenderWidget.hpp"

using Geo::LogViewer::RenderWidgets::GenericRenderWidget;
using Geo::LogViewer::SectionControllers::AbstractSectionController;

GenericRenderWidget::
GenericRenderWidget(
  Scalers::Scaler::Pointer scaler,
  SectionControllers::AbstractSectionController::Pointer
  rootSection):
  _scaler(scaler),
  _rootSection(rootSection)
{
  setAutoFillBackground(false);
}


AbstractSectionController::Pointer
GenericRenderWidget::
rootSection() const
{
  return _rootSection;
}


void
GenericRenderWidget::
paint(SectionControllers::AbstractSectionController* section,
      QPainter&                                      painter,
      Scalers::Scaler::Pointer                       scaler,
      QRectF                                         rect)
{
  Q_UNUSED(section);
  Q_UNUSED(painter);
  Q_UNUSED(scaler);
  Q_UNUSED(rect);
}
