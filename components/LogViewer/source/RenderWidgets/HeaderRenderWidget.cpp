#include "HeaderRenderWidget.hpp"

#include <QPaintEvent>
#include <QPainter>

namespace Geo {
namespace LogViewer {
namespace RenderWidgets {
HeaderRenderWidget::
HeaderRenderWidget(
  Scalers::Scaler::Pointer                  scaler,
  QSharedPointer<SectionControllers::
                 AbstractSectionController> rootSection):
  GenericRenderWidget(scaler, rootSection)
{}

void
HeaderRenderWidget::
paintEvent(QPaintEvent* event)
{
  QPainter
    painter(this);

  // background
  painter.fillRect(event->rect(), QColor(Qt::gray).lighter(120));

  /// transforms meters of real well to meters of "paper" for printing
  QTransform t = _scaler->getTransform();

  // apply transformation
  painter.setTransform(t);

  QRectF
    paintRect(event->rect());

  paintRect = t.inverted().mapRect(paintRect);

  paint(_rootSection.data(), painter, _scaler, paintRect);
}


void
HeaderRenderWidget::
wheelEvent(QWheelEvent* event)
{
  Q_UNUSED(event);
}


void
HeaderRenderWidget::
timerEvent(QTimerEvent* event)
{
  Q_UNUSED(event);
}


void
HeaderRenderWidget::
mousePressEvent(QMouseEvent* event)
{
  Q_UNUSED(event);
}


void
HeaderRenderWidget::
mouseReleaseEvent(QMouseEvent* event)
{
  Q_UNUSED(event);
}


void
HeaderRenderWidget::
mouseMoveEvent(QMouseEvent* event)
{
  Q_UNUSED(event);
}


void
HeaderRenderWidget::
paint(SectionControllers::AbstractSectionController* section,
      QPainter&                                      painter,
      Scalers::Scaler::Pointer                       scaler,
      QRectF                                         rect)
{
  // first, we get view -- it does all painting
  SectionViews::AbstractSectionView::Pointer sectionView = section->getView();

  painter.save();
  sectionView->paintHeader(painter, scaler, rect);
  painter.restore();

  QListIterator<SectionControllers::AbstractSectionController*> it =
    section->getChildSectionsIterator();

  painter.save();
  {
    sectionView->preOffsetPainterForHeader(painter);

    // now we draw child sections recursively
    while (it.hasNext())
      paint(it.next(), painter, scaler, rect);
  }
  painter.restore();

  sectionView->postOffsetPainterForHeader(painter);
}
}
}
}
