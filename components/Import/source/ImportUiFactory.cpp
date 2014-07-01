#include "ImportUiFactory.hpp"

#include <QAction>
#include <QIcon>
#include <QList>
#include <QMenu>
#include <QToolBar>

#include <Core/MainWindow>

#include <DependencyManager/ApplicationContext>

#include <Uni/Logging/Logging>

#include "ImportController.hpp"

using Geo::Import::ImportUiFactory;

class ImportUiFactory::Private {
public:
  Private():
    _menu(new QMenu(tr("Import"))),
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

    action = new QAction(QIcon(), QString("Las Files"), mainWindow);

    connect(action,
            &QAction::triggered,
            ImportController::instance(),
            &ImportController::selectFilesAndImport);

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

// --------------------------------------------------

Q_INVOKABLE
ImportUiFactory::
ImportUiFactory():
  _p(new Private())
{
  _p->fillActionList();
  _p->constructMenu();
  // _p->constructToolBar();
}


ImportUiFactory::
~ImportUiFactory()
{
  delete _p;
}


Q_INVOKABLE QMenu*
ImportUiFactory::
getImportMenu()
{
  return _p->_menu;
}


Q_INVOKABLE QToolBar*
ImportUiFactory::
getImportToolBar()
{
  return _p->_toolBar;
}
