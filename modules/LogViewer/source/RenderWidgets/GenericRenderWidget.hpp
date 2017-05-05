#ifndef Geo_LogViewer_RenderWidgets_GenericRenderWidget_hpp
#define Geo_LogViewer_RenderWidgets_GenericRenderWidget_hpp

#include <QPainter>
#include <QRectF>
#include <QTransform>
#include <QWidget>

#include "../Scalers/Scaler.hpp"
#include "../SectionControllers/AbstractSectionController.hpp"

namespace Geo {
namespace LogViewer {
namespace RenderWidgets {
// represents a wiget where LogViewer drawing happens
class GenericRenderWidget: public QWidget {
  Q_OBJECT

public:
  explicit
  GenericRenderWidget(
    Scalers::Scaler::Pointer                               scaler,
    SectionControllers::AbstractSectionController::Pointer rootSection);

  virtual
  ~GenericRenderWidget() {}

  SectionControllers::AbstractSectionController::Pointer
  rootSection()
  const;

protected:
  Scalers::Scaler::Pointer                                      _scaler;
  QSharedPointer<SectionControllers::AbstractSectionController> _rootSection;

  virtual
  void
  paint(SectionControllers::AbstractSectionController* section,
        QPainter&                                      painter,
        Scalers::Scaler::Pointer                       scaler,
        QRectF                                         rect);
};
} // RenderWidgets
} // namespace LogViewer
} // namespace Geo

#endif // Geo_LogViewer_RenderWidgets_GenericRenderWidget_hpp
