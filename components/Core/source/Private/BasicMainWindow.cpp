#include "BasicMainWindow.hpp"

#include "Auxiliary/ExecutionControl.hpp"

#include <QDebug>

#include <QMdiArea>
#include <QMdiSubWindow>
// --

using Geo::Core::Private::BasicMainWindow;

BasicMainWindow::
BasicMainWindow()
{
  INFO << "BasicMainWindow is being created";

  QMdiArea* _mdiArea = new QMdiArea(this);

  setCentralWidget(_mdiArea);

  showMaximized();
}

BasicMainWindow::
~BasicMainWindow()
{
  INFO << "BasicMainWindow is being destroyed";
}

Q_INVOKABLE void
BasicMainWindow::
toBottomDock(QDockWidget* dockWidget)
{
  DEBUG << "BasicMainWindow::toBottomDock(QDockWidget* dockWidget) is being invoked";

  addDockWidget(Qt::BottomDockWidgetArea, dockWidget);
}

Q_INVOKABLE void
BasicMainWindow::
toLeftDock(QDockWidget* dockWidget)
{
  DEBUG << "BasicMainWindow::toLeftDock(QDockWidget* dockWidget) is being invoked";

  addDockWidget(Qt::LeftDockWidgetArea, dockWidget);
}

Q_INVOKABLE void
BasicMainWindow::
toRightDock(QDockWidget* dockWidget)
{
  DEBUG << "BasicMainWindow::toRightDock(QDockWidget* dockWidget) is being invoked";

  addDockWidget(Qt::RightDockWidgetArea, dockWidget);
}
