#ifndef Geo_LogViewer_LogViewerWidgetFactory_hpp
#define Geo_LogViewer_LogViewerWidgetFactory_hpp

#include <QObject>

class QWidget;

namespace Geo {
namespace LogViewer {
class LogViewerWidgetFactory : public QObject {
  Q_OBJECT

public:
  Q_INVOKABLE
  LogViewerWidgetFactory();

  virtual
  ~LogViewerWidgetFactory();

  Q_INVOKABLE QWidget*
  createLogViewerWidget() const;
};
}
}

#endif // Geo_LogViewer_LogViewerWidgetFactory_hpp
