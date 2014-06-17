#include "MultiWellSectionView.hpp"

#include <QPainter>
#include <QRectF>

#include "../SectionControllers/AbstractSectionController.hpp"

#include "AbstractSectionView.hpp"
#include "WellView.hpp"

using Geo::LogViewer::SectionViews::MultiWellSectionView;

MultiWellSectionView::
MultiWellSectionView(
  SectionControllers::AbstractSectionController* controller)
// Domain::LogView::Pointer                       logView)
      : AbstractSectionView(controller)
        // , _logView(logView)
{}

void
MultiWellSectionView::
paintHeader(QPainter&                painter,
            Scalers::Scaler::Pointer scaler,
            QRectF&                  rect)
{
  Q_UNUSED(painter);
  Q_UNUSED(scaler);
  Q_UNUSED(rect);
}


void
MultiWellSectionView::
paintBody(QPainter& painter, Scalers::Scaler::Pointer scaler, QRectF& rect)
{
  Q_UNUSED(painter);
  Q_UNUSED(scaler);
  Q_UNUSED(rect);
}
