#include "BodyRenderWidget.hpp"

#include <QPainter>
#include <QWheelEvent>

#include "../Scalers/Scaler.hpp"

#include "../SectionViews/AbstractSectionView.hpp"

using Geo::LogViewer::RenderWidgets::BodyRenderWidget;

BodyRenderWidget::
BodyRenderWidget(
  Scalers::Scaler::Pointer                               scaler,
  SectionControllers::AbstractSectionController::Pointer rootSection):

  GenericRenderWidget(scaler, rootSection),
  _bodyMouseInputFilter(this, _scaler, _rootSection)
{
  setMouseTracking(true);
}


void
BodyRenderWidget::
wheelEvent(QWheelEvent* event)
{
  _bodyMouseInputFilter.wheelEvent(event);
}


void
BodyRenderWidget::
mousePressEvent(QMouseEvent* event)
{
  _bodyMouseInputFilter.mousePressEvent(event);
}


void
BodyRenderWidget::
mouseReleaseEvent(QMouseEvent* event)
{
  _bodyMouseInputFilter.mouseReleaseEvent(event);
}


void
BodyRenderWidget::
mouseMoveEvent(QMouseEvent* event)
{
  _bodyMouseInputFilter.mouseMoveEvent(event);
}


void
BodyRenderWidget::
resizeEvent(QResizeEvent* event)
{
  _bodyMouseInputFilter.resizeEvent(event);
}


void
BodyRenderWidget::
paintEvent(QPaintEvent* event)
{
  QPainter painter(this);

  // gray background
  painter.fillRect(event->rect(), QColor(Qt::gray).lighter(120));

  // transforms meters of real well to pixels
  QTransform t = _scaler->getTransform();

  // TODO include this offset into scaler
  t.translate(0, -_rootSection->topDepth());

  // apply transformation
  painter.setTransform(t);

  QRectF paintRect(event->rect());

  paintRect = t.inverted().mapRect(paintRect);

  paint(_rootSection.data(), painter, _scaler, paintRect);
}


void
BodyRenderWidget::
paint(SectionControllers::AbstractSectionController* section,
      QPainter&                                      painter,
      Scalers::Scaler::Pointer                       scaler,
      QRectF                                         rect)
{
  // first, we get view -- it does all painting
  SectionViews::AbstractSectionView::Pointer sectionView = section->getView();

  painter.save();
  sectionView->paintBody(painter, scaler, rect);
  painter.restore();

  QListIterator<SectionControllers::AbstractSectionController*> it =
    section->getChildSectionsIterator();

  painter.save();
  {
    sectionView->preOffsetPainterForBody(painter);

    // now we draw child sections recursively
    while (it.hasNext())
      paint(it.next(), painter, scaler, rect);
  }
  painter.restore();

  sectionView->postOffsetPainterForBody(painter);
}
