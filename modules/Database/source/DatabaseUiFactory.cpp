#include "DatabaseUiFactory.hpp"

#include <QtWidgets/QAction>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QMenu>
#include <QtWidgets/QToolBar>

#include <QtCore/QList>

#include <Core/MainWindow>

#include <ComponentManager/Creator>

#include "DatabaseController.hpp"

using Geo::Database::DatabaseUiFactory;

DatabaseUiFactory::
DatabaseUiFactory()
{
  //
}


DatabaseUiFactory::
~DatabaseUiFactory()
{
  //
}


QMenu*
DatabaseUiFactory::
createDatabaseMenu()
{
  QMenu* menu = new QMenu(tr("Database"));

  auto actionList = createActionList();

  for (QAction* action : actionList)
    menu->addAction(action);

  return menu;
}


QToolBar*
DatabaseUiFactory::
createDatabaseToolBar()
{
  return nullptr;
}


std::vector<QAction*>
DatabaseUiFactory::
createActionList() const
{
  using Geo::Core::MainWindow;

  MainWindow* mainWindow = ComponentManager::create<MainWindow*>("Core.MainWindow");

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
            &in, &DatabaseController::showSettingsWidget);

    actionList.push_back(action);
  }

  // ---------------

  return actionList;
}
