#ifndef Geo_LogViewer_LogViewerUiFactory_hpp
#define Geo_LogViewer_LogViewerUiFactory_hpp

#include <QObject>

class QWidget;
class QMenu;

namespace Geo {
namespace LogViewer {
class LogViewerUiFactory: public QObject {
  Q_OBJECT

public:
  Q_INVOKABLE
  LogViewerUiFactory();

  virtual
  ~LogViewerUiFactory();

public:
  Q_INVOKABLE
  QMenu*
  getLogViewerMenu();

private:
  class Private;
  Private* _p;
};
}
}

#endif // Geo_LogViewer_LogViewerUiFactory_hpp
