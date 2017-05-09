#include "BasicMainWindow.hpp"

#include <QtCore/QDebug>

#include <QtWidgets/QDockWidget>
#include <QtWidgets/QMdiArea>
#include <QtWidgets/QMdiSubWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
// --

using Geo::Core::Private::BasicMainWindow;

BasicMainWindow::
BasicMainWindow()
  : _mdiArea(new QMdiArea(this))
  , _statusBar(statusBar())
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
addMenu(QObject* menu)
{
  menuBar()->addMenu((QMenu*)menu);
}


Q_INVOKABLE void
BasicMainWindow::
addToolBar(QToolBar* toolBar)
{
  QMainWindow::addToolBar(toolBar);
}


void
BasicMainWindow::
setStatus(QString status)
{
  _statusBar->showMessage(status, 4000);
}
