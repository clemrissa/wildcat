#pragma once

#include <QtCore/QString>
#include <QtWidgets/QMainWindow>

namespace Geo {
namespace Core {
//

class IMainWindow : public QMainWindow
{
public:
  virtual void
  toCentralWidget(QWidget* widget) = 0;

  virtual void
  toLeftDock(QWidget* dockWidget) = 0;

public slots:
  virtual void
  setStatus(QString status) = 0;
};

//
}
}
