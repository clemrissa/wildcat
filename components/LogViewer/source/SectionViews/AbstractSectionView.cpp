#include "AbstractSectionView.hpp"

#include "../SectionControllers/AbstractSectionController.hpp"

using Geo::LogViewer::SectionControllers::AbstractSectionController;
using Geo::LogViewer::SectionViews::AbstractSectionView;

AbstractSectionView::
AbstractSectionView(
  SectionControllers::AbstractSectionController* controller):
  _controller(controller)
{}

AbstractSectionController const*
AbstractSectionView::
controller() const
{
  return _controller;
}
