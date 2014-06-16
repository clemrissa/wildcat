#ifndef Geo_LogViewer_LogViewerController_hpp
#define Geo_LogViewer_LogViewerController_hpp

#include <QObject>

namespace Geo {
namespace LogViewer {
class LogViewerController: public QObject {
  Q_OBJECT

public:
  static LogViewerController*
  instance();

  virtual
  ~LogViewerController();

public slots:
  void
  createLogViewer();

private:
  LogViewerController();

private:
  static LogViewerController* _instance;
};
}
}
#endif //  Geo_LogViewer_LogViewerController_hpp
