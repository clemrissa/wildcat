#include "BasicMainWindow.hpp"

#include <QtCore/QDebug>

#include <QtWidgets/QDockWidget>
#include <QtWidgets/QMdiArea>
#include <QtWidgets/QMdiSubWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>

#include <ComponentManager/Creator>

namespace Geo
{
namespace Core
{

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
toLeftDock(QWidget* widget)
{
  widget->setMinimumSize(QSize(200,200));

  QDockWidget * dockWidget = new QDockWidget(widget->windowTitle(), this);

  dockWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

  dockWidget->setWidget(widget);


  addDockWidget(Qt::LeftDockWidgetArea, dockWidget);

  QMenu *m = ComponentManager::create<QMenu*>("Database.Menu");

  m->addAction(dockWidget->toggleViewAction());

  // TODO: required?
  widget->show();
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


//
}
}
