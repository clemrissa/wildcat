#ifndef Geo_Logviwer_SectionViews_AbstractSectionView_hpp
#define Geo_Logviwer_SectionViews_AbstractSectionView_hpp

#include <QObject>
#include <QRectF>
#include <QSharedPointer>

#include "../Scalers/Scaler.hpp"

class QPainter;
class QPaintEvent;

namespace Geo {
namespace LogViewer {
namespace SectionControllers {
class AbstractSectionController;
}
namespace SectionViews {
class AbstractSectionView : public QObject {
  Q_OBJECT

public:
  typedef QSharedPointer<AbstractSectionView> Pointer;

  AbstractSectionView(
    SectionControllers::AbstractSectionController* controller);

  virtual
  ~AbstractSectionView() {}

  virtual void
  paintHeader(QPainter&                painter,
              Scalers::Scaler::Pointer scaler,
              QRectF&                  r) = 0;

  virtual void
  paintBody(QPainter&                painter,
            Scalers::Scaler::Pointer scaler,
            QRectF&                  r) = 0;

  SectionControllers::AbstractSectionController const*
  controller() const;

  // changes Painter before painting a section
  virtual void
  preOffsetPainterForHeader(QPainter& painter) { Q_UNUSED(painter); }

  virtual void
  preOffsetPainterForBody(QPainter& painter) { Q_UNUSED(painter); }

  // changes Painter after painting a section
  virtual void
  postOffsetPainterForHeader(QPainter& painter) { Q_UNUSED(painter); }

  virtual void
  postOffsetPainterForBody(QPainter& painter) { Q_UNUSED(painter); }

protected:
  SectionControllers::AbstractSectionController* _controller;
};
}
}
}

#endif // Geo_Logviwer_SectionViews_AbstractSectionView_hpp
