#include "BodyMouseInputFilter.hpp"

#include "../RenderWidgets/GenericRenderWidget.hpp"

namespace Geo {
namespace LogViewer {
namespace MouseInputFilters {
BodyMouseInputFilter::
BodyMouseInputFilter(
  RenderWidgets::GenericRenderWidget*                    widget,
  Scalers::Scaler::Pointer                               scaler,
  SectionControllers::AbstractSectionController::Pointer rootSection):
  GenericMouseInputFilter(widget, scaler, rootSection)
{}

void
BodyMouseInputFilter::
mousePressEvent(QMouseEvent* event)
{
  _lastPoint = event->pos();

  event->accept();
}


void
BodyMouseInputFilter::
mouseReleaseEvent(QMouseEvent* event)
{
  event->accept();
}


void
BodyMouseInputFilter::
mouseMoveEvent(QMouseEvent* event)
{
  if (Qt::LeftButton & event->buttons()) {
    QPoint offset = event->pos() - _lastPoint;

    // first X direction
    xOvershootControl(offset.x());

    // then Y direction
    yOvershootControl(offset.y());

    _widget->update();
  }

  _lastPoint = event->pos();

  event->accept();

  //        QApplication::sendEvent(rootSection_.data(), &renderWindowEvent);
}


void
BodyMouseInputFilter::
resizeEvent(QResizeEvent* event)
{
  Q_UNUSED(event);

  xOvershootControl(0);

  yOvershootControl(0);

  _widget->update();
}


void
BodyMouseInputFilter::
wheelEvent(QWheelEvent* event)
{
  double mult = event->delta() > 0 ? 1.25 : 1.0 / 1.25;

  // y scaling
  if (Qt::ShiftModifier & event->modifiers()) {
    double y = event->y() - _scaler->yOffset();

    _scaler->multiplyYScale(mult);

    // TODO do not do this if schale was not changed
    yOvershootControl(y - y * mult);

    event->accept();
  }
  // x scaling
  else if (Qt::ControlModifier & event->modifiers()) {
    double x = event->x() - _scaler->xOffset();

    _scaler->multiplyXScale(mult);

    // TODO do not do this if schale was not changed
    xOvershootControl(x - x * mult);

    event->accept();
    // simple scrolling
  } else {
    int d = event->delta() / 10;

    switch (event->orientation()) {
    case Qt::Horizontal:
      xOvershootControl(d);
      break;

    case Qt::Vertical:
      yOvershootControl(d);
      break;
    }

    event->accept();
  }

  _widget->update();
}


void
BodyMouseInputFilter::
xOvershootControl(int offset)
{
  int rootSectionWidth = _scaler->xScaler()->scaleRealCoordsToPixels(
    _rootSection->width());

  if (rootSectionWidth < _widget->width())
    // center aligment
    _scaler->setXOffset(_widget->width() / 2 - rootSectionWidth / 2);

  else {
    _scaler->addToXOffset(offset);

    if (_scaler->xOffset() > 0)
      _scaler->setXOffset(0);

    if (_scaler->xOffset() + rootSectionWidth < _widget->width())
      _scaler->setXOffset(_widget->width() - rootSectionWidth);
  }
}


void
BodyMouseInputFilter::
yOvershootControl(int offset)
{
  int rootSectionHeight = _scaler->yScaler()->scaleRealCoordsToPixels(
    _rootSection->height());

  if (rootSectionHeight < _widget->height())
    // top aligment
    _scaler->setYOffset(0);

  else {
    _scaler->addToYOffset(offset);

    if (_scaler->yOffset() > 0)
      _scaler->setYOffset(0);

    if (_scaler->yOffset() + rootSectionHeight < _widget->height() * 2 / 3)
      _scaler->setYOffset(_widget->height() * 2 / 3 - rootSectionHeight);
  }
}
}
}
}
