#include "BasicMainWindow.hpp"

#include "Auxiliary/ExecutionControl.hpp"

#include <QDebug>

#include <QDockWidget>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
// --

using Geo::Core::Private::BasicMainWindow;

BasicMainWindow::
BasicMainWindow():
  _mdiArea(new QMdiArea(this)) {
  INFO << "BasicMainWindow is being created";

  setCentralWidget(_mdiArea);

  showMaximized();
}

BasicMainWindow::
~BasicMainWindow() {
  INFO << "BasicMainWindow is being destroyed";
}

Q_INVOKABLE void
BasicMainWindow::
toBottomDock(QDockWidget* dockWidget) {
  DEBUG <<
    "BasicMainWindow::toBottomDock(QDockWidget* dockWidget) is being invoked";

  addDockWidget(Qt::BottomDockWidgetArea, dockWidget);
}

Q_INVOKABLE void
BasicMainWindow::
toLeftDock(QDockWidget* dockWidget) {
  DEBUG <<
    "BasicMainWindow::toLeftDock(QDockWidget* dockWidget) is being invoked";

  addDockWidget(Qt::LeftDockWidgetArea, dockWidget);
}

Q_INVOKABLE void
BasicMainWindow::
toRightDock(QDockWidget* dockWidget) {
  DEBUG <<
    "BasicMainWindow::toRightDock(QDockWidget* dockWidget) is being invoked";

  addDockWidget(Qt::RightDockWidgetArea, dockWidget);
}

Q_INVOKABLE void
BasicMainWindow::
toCentralWidget(QWidget* widget) {
  DEBUG <<
    "BasicMainWindow::toCentralWidget(QWidget* dockWidget) is being invoked";

  QMdiSubWindow* subWindow = _mdiArea->addSubWindow(widget);
  subWindow->show();
}

Q_INVOKABLE void
BasicMainWindow::
addMenu(QMenu* menu) {
  DEBUG << "BasicMainWindow::addMenu(QMenu* menu) is invoked";
  menuBar()->addMenu(menu);
}

Q_INVOKABLE void
BasicMainWindow::
addToolBar(QToolBar* toolBar) {
  DEBUG << "BasicMainWindow::addToolBar(QToolBar* toolBar) is invoked";
  QMainWindow::addToolBar(toolBar);
}
