#pragma once

#include <QtCore/QObject>

namespace Geo {
namespace LogViewer {
class LogViewerController : public QObject
{
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
