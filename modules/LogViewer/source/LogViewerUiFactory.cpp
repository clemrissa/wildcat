#include "LogViewerUiFactory.hpp"

#include <QLabel>
#include <QMenu>
#include <QToolBar>
#include <QWidget>

#include <Core/IMainWindow>

#include <ComponentManager/Creator>

#include "LogViewerController.hpp"

using Geo::LogViewer::LogViewerUiFactory;

class LogViewerUiFactory::Private
{
public:
  Private()
    : _menu(new QMenu(tr("LogViewer")))
    , _toolBar(new QToolBar())
  {}

  void
  fillActionList()
  {
    using Geo::Core::IMainWindow;

    IMainWindow* mainWindow =
      ComponentManager::create<IMainWindow*>("Core.MainWindow");

    QAction* action = nullptr;

    action = new QAction(QIcon(), QString("Create"), mainWindow);

    connect(action, &QAction::triggered,
            &LogViewerController::instance(),
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
  QMenu* _menu;
  QToolBar* _toolBar;

  QList<QAction*> _actionList;
};

// --------------------------

LogViewerUiFactory::
LogViewerUiFactory()
  : _p(std::make_unique<Private>())
{
  _p->fillActionList();
  _p->constructMenu();
}


LogViewerUiFactory::
~LogViewerUiFactory()
{}


QObject*
LogViewerUiFactory::
getLogViewerMenu()
{
  return _p->_menu;
}
