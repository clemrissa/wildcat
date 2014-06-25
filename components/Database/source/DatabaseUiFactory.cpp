#include "DatabaseUiFactory.hpp"

#include <QDockWidget>
#include <QMenu>
#include <QToolBar>

#include <QAction>
#include <QList>

#include <Core/MainWindow>
#include <DependencyManager/ApplicationContext>
#include <Uni/Logging/Logging>

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

QList<QAction*>
DatabaseUiFactory::
createActionList() const
{
  using DependencyManager::ApplicationContext;
  using Geo::Core::MainWindow;

  MainWindow* mainWindow =
    DependencyManager::ApplicationContext::create<MainWindow>("Core.MainWindow");

  DatabaseController* in = DatabaseController::instance();

  QList<QAction*> actionList;

  // ---------------

  QAction* action = new QAction(QIcon(), QString("Connections"), mainWindow);

  connect(action, &QAction::triggered,
          in, &DatabaseController::showConnectionsWidget);

  actionList.append(action);

  // ---------------

  action = new QAction(QIcon(), tr("Settings"), mainWindow);

  connect(action, &QAction::triggered,
          in, &DatabaseController::showSettingsWidget);

  actionList.append(action);

  // ---------------

  return actionList;
}
