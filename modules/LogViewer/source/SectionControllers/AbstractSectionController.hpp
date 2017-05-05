#ifndef Geo_LogViewer_SectionControllers_AbstractSectionController_hpp
#define Geo_LogViewer_SectionControllers_AbstractSectionController_hpp

#include <QList>
#include <QObject>
#include <QRectF>
#include <QSharedPointer>

#include "../Scalers/Scaler.hpp"

#include "../SectionViews/AbstractSectionView.hpp"

class QPainter;
class QPaintEvent;

namespace Geo {
namespace LogViewer {
namespace SectionControllers {
class AbstractSectionController: public QObject {
  Q_OBJECT
  Q_PROPERTY(double topDepth \
             READ topDepth)

  Q_PROPERTY(double bottomDepth \
             READ bottomDepth)

  Q_PROPERTY(double width \
             READ width)

  Q_PROPERTY(double height \
             READ height)

public:
  typedef QSharedPointer<AbstractSectionController> Pointer;

public:
  AbstractSectionController(AbstractSectionController* parent);

  virtual
  ~AbstractSectionController();

public:
  // TODO remove LogViewer from the function name
  void
  addChildLogViewerSection(AbstractSectionController* AbstractSectionController);

  /// @returns bottom in meters
  virtual double
  topDepth() const = 0;

  /// @returns top in meters
  virtual double
  bottomDepth() const = 0;

  /// @returns width in in meters
  virtual double
  width() const = 0;

  virtual double
  height() { return bottomDepth() - topDepth(); }

  virtual bool
  hasDepthLimits() = 0;

  virtual
  SectionViews::AbstractSectionView::Pointer
  getView() const = 0;

public:
  // virtual functions
  virtual
  AbstractSectionController const*
  parent() const;

  virtual void
  recalculateSize();

  QListIterator<AbstractSectionController*>
  getChildSectionsIterator() const;

signals:
  void
  topDepthChanged();

  void
  bottomDepthChanged();

  void
  widthChanged();

protected:
  void
  customEvent(QEvent* event);

  virtual void
  recalculateWidth();

  virtual void
  recalculateDepths();

protected:
  // List of child controllers
  QList<AbstractSectionController*> _sectionControllersList;

  // Parent controller
  AbstractSectionController* _parent;

  double _topDepth;
  double _bottomDepth;
  double _width;
};
}
}
}

#endif // Geo_Logviwer_Scalers_AbstractSectionController_hpp
