#include "DatabaseUiFactory.hpp"

#include <QtWidgets/QAction>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QMenu>
#include <QtWidgets/QToolBar>

#include <QtCore/QList>

#include <Core/IMainWindow>

#include <ComponentManager/Creator>

#include "DatabaseController.hpp"

using Geo::Database::DatabaseUiFactory;

DatabaseUiFactory::
DatabaseUiFactory()
{
  createDatabaseMenu();
}


DatabaseUiFactory::
~DatabaseUiFactory()
{
  //
}


QMenu*
DatabaseUiFactory::
databaseMenu() const
{
  return _databaseMenu;
}


QToolBar*
DatabaseUiFactory::
createDatabaseToolBar()
{
  return nullptr;
}


void
DatabaseUiFactory::
createDatabaseMenu()
{
  _databaseMenu = new QMenu(tr("Database"));

  auto actionList = createActionList();

  for (QAction* action : actionList)
    _databaseMenu->addAction(action);
}


std::vector<QAction*>
DatabaseUiFactory::
createActionList() const
{
  using Geo::Core::IMainWindow;

  IMainWindow* mainWindow = ComponentManager::create<IMainWindow*>("Core.MainWindow");

  DatabaseController& in = DatabaseController::instance();

  std::vector<QAction*> actionList;

  // ---------------

  {
    QAction* action = new QAction(QIcon(), QString("Connections"), mainWindow);

    connect(action, &QAction::triggered,
            &in, &DatabaseController::showConnectionsWidget);

    actionList.push_back(action);
  }

  {
    QAction* action = new QAction(QIcon(), tr("Well Traits"), mainWindow);

    connect(action, &QAction::triggered,
            &in, &DatabaseController::showTraitsWidget);

    actionList.push_back(action);
  }

  // ---------------

  return actionList;
}
