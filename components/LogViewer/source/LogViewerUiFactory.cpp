#include "LogViewerUiFactory.hpp"

#include <QLabel>
#include <QMenu>
#include <QToolBar>
#include <QWidget>

#include <Core/MainWindow>

#include <DependencyManager/ApplicationContext>

#include "LogViewerController.hpp"

using Geo::LogViewer::LogViewerUiFactory;

class LogViewerUiFactory::Private {
public:
  Private():
    _menu(new QMenu(tr("LogViewer"))),
    _toolBar(new QToolBar())
  {}

  void
  fillActionList()
  {
    using DependencyManager::ApplicationContext;
    using Geo::Core::MainWindow;

    MainWindow* mainWindow =

      DependencyManager::ApplicationContext::create<MainWindow>("Core.MainWindow");

    QAction* action = nullptr;

    action = new QAction(QIcon(), QString("Create"), mainWindow);

    connect(action, &QAction::triggered,
            LogViewerController::instance(),
            &LogViewerController::createLogViewer);

    _actionList.append(action);
  }


  void
  constructMenu()
  {
    for (QAction* action : _actionList)
      _menu->addAction(action);
  }


  void
  constructToolBar()
  {
    for (QAction* action : _actionList)
      _toolBar->addAction(action);
  }


public:
  QMenu*    _menu;
  QToolBar* _toolBar;

  QList<QAction*> _actionList;
};

// --------------------------

LogViewerUiFactory::
LogViewerUiFactory():
  _p(new Private())
{
  _p->fillActionList();
  _p->constructMenu();
}


LogViewerUiFactory::
~LogViewerUiFactory()
{
  delete _p;
}


Q_INVOKABLE QMenu*
LogViewerUiFactory::
getLogViewerMenu()
{
  return _p->_menu;
}
