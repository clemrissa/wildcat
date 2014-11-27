#include "TypeSystemUiFactory.hpp"

#include <QtWidgets/QAction>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QMenu>
#include <QtWidgets/QToolBar>

#include <QtCore/QList>

#include <Core/MainWindow>
#include <DependencyManager/ApplicationContext>
#include <Uni/Logging/Logging>

#include "TypeSystemController.hpp"

using Geo::TypeSystem::TypeSystemUiFactory;

TypeSystemUiFactory::
TypeSystemUiFactory()
{
  //
}


TypeSystemUiFactory::
~TypeSystemUiFactory()
{
  //
}


QMenu*
TypeSystemUiFactory::
createTypeSystemMenu()
{
  // core menu attached to the bar
  QMenu* menu = new QMenu(tr("Type System"));

  auto actionList = createActionList();

  for (QAction* action : actionList)
    menu->addAction(action);

  return menu;
}


QToolBar*
TypeSystemUiFactory::
createTypeSystemToolBar()
{
  return nullptr;
}


QList<QAction*>
TypeSystemUiFactory::
createActionList() const
{
  using DependencyManager::ApplicationContext;
  using Geo::Core::MainWindow;

  //MainWindow* mainWindow =
    //DependencyManager::ApplicationContext::create<MainWindow>("Core.MainWindow");

  //TypeSystemController* in = TypeSystemController::instance();

  QList<QAction*> actionList;

  // ---------------

  //QAction* action = new QAction(QIcon(), QString("Connections"), mainWindow);

  //connect(action, &QAction::triggered,
          //in, &TypeSystemController::showConnectionsWidget);

  //actionList.append(action);

  //// ---------------

  //action = new QAction(QIcon(), tr("Well Traits"), mainWindow);

  //connect(action, &QAction::triggered,
          //in, &TypeSystemController::showSettingsWidget);

  //actionList.append(action);

  // ---------------

  return actionList;
}
