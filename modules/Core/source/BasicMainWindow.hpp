#pragma once

#include <MainWindow.hpp>

class QDockWidget;
class QMdiArea;
class QToolBar;
class QMenu;
class QStatusBar;

namespace Geo {
namespace Core {
namespace Private {
//

class BasicMainWindow : public Geo::Core::MainWindow
{
  Q_OBJECT

public:
  Q_INVOKABLE
  BasicMainWindow();

  virtual
  ~BasicMainWindow();

  Q_INVOKABLE void
  toBottomDock(QDockWidget* dockWidget);

  Q_INVOKABLE void
  toLeftDock(QDockWidget* dockWidget);

  Q_INVOKABLE void
  toRightDock(QDockWidget* dockWidget);

  Q_INVOKABLE void
  toCentralWidget(QWidget* widget) override;

  Q_INVOKABLE void
  addMenu(QObject* menu);

  Q_INVOKABLE void
  addToolBar(QToolBar* toolBar);

public slots:
  virtual void
  setStatus(QString status) override;

private:
  QMdiArea* _mdiArea;

  QStatusBar* _statusBar;
};
}
}
}