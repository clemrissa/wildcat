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
  _mdiArea(new QMdiArea(this))
{
  setCentralWidget(_mdiArea);

  showMaximized();
}


BasicMainWindow::
~BasicMainWindow()
{
  //
}


Q_INVOKABLE void
BasicMainWindow::
toBottomDock(QDockWidget* dockWidget)
{
  addDockWidget(Qt::BottomDockWidgetArea, dockWidget);
}


Q_INVOKABLE void
BasicMainWindow::
toLeftDock(QDockWidget* dockWidget)
{
  addDockWidget(Qt::LeftDockWidgetArea, dockWidget);
}


Q_INVOKABLE void
BasicMainWindow::
toRightDock(QDockWidget* dockWidget)
{
  addDockWidget(Qt::RightDockWidgetArea, dockWidget);
}


Q_INVOKABLE void
BasicMainWindow::
toCentralWidget(QWidget* widget)
{
  QMdiSubWindow* subWindow = _mdiArea->addSubWindow(widget);

  subWindow->setAttribute(Qt::WA_DeleteOnClose);

  subWindow->show();
}


Q_INVOKABLE void
BasicMainWindow::
addMenu(QMenu* menu)
{
  menuBar()->addMenu(menu);
}


Q_INVOKABLE void
BasicMainWindow::
addToolBar(QToolBar* toolBar)
{
  QMainWindow::addToolBar(toolBar);
}
