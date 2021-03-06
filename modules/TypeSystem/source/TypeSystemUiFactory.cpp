#include "TypeSystemUiFactory.hpp"

#include <QtWidgets/QAction>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QMenu>
#include <QtWidgets/QToolBar>

#include <QtCore/QList>

#include <Core/IMainWindow>
#include <ComponentManager/Creator>

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


QObject*
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
  using Geo::Core::IMainWindow;

  IMainWindow* mainWindow = ComponentManager::create<IMainWindow*>("Core.MainWindow");

  TypeSystemController & typeSystemController = TypeSystemController::instance();

  QList<QAction*> actionList;

  // ---------------

  auto action = new QAction(QIcon(), tr("Curve Types"), mainWindow);

  connect(action, &QAction::triggered,
          &typeSystemController, &TypeSystemController::showCurveTypeWidget);

  actionList.append(action);

  // ---------------

  action = new QAction(QIcon(), tr("Units"), mainWindow);

  connect(action, &QAction::triggered,
          &typeSystemController, &TypeSystemController::showUnitsWidget);

  actionList.append(action);

  return actionList;
}
