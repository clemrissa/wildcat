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


QObject*
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
  using Geo::Core::MainWindow;

  MainWindow* mainWindow =
    ComponentManager::create<MainWindow*>("Core.MainWindow");

  DatabaseController* in = DatabaseController::instance();

  QList<QAction*> actionList;

  // ---------------

  QAction* action = new QAction(QIcon(), QString("Connections"), mainWindow);

  connect(action, &QAction::triggered,
          in, &DatabaseController::showConnectionsWidget);

  actionList.append(action);

  // ---------------

  action = new QAction(QIcon(), tr("Well Traits"), mainWindow);

  connect(action, &QAction::triggered,
          in, &DatabaseController::showSettingsWidget);

  actionList.append(action);

  // ---------------

  return actionList;
}
