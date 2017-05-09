#pragma once

#include <QtCore/QObject>

class QWidget;
class QMenu;

namespace Geo {
namespace LogViewer {
class LogViewerUiFactory : public QObject
{
  Q_OBJECT

public:
  Q_INVOKABLE
  LogViewerUiFactory();

  virtual
  ~LogViewerUiFactory();

public:
  Q_INVOKABLE
  QObject*
  getLogViewerMenu();

private:
  class Private;
  Private* _p;
};
}
}
