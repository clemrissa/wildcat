#include "TypeSystemController.hpp"

#include <QtWidgets/QLabel>

#include <Core/MainWindow>
#include <ComponentManager/Creator>

#include <Widgets/IConnectionDrivenWidget>

#include "Gui/CurveTypes/CurveTypeWidget.hpp"
#include "Gui/Units/UnitWidget.hpp"

namespace Geo
{
namespace TypeSystem
{
//

TypeSystemController &
TypeSystemController::
instance()
{
  static TypeSystemController instance;

  return instance;
}


TypeSystemController::
TypeSystemController()
{
  //
}


TypeSystemController::
~TypeSystemController()
{
  //
}


void
TypeSystemController::
showCurveTypeWidget()
{
  using Geo::Core::MainWindow;
  using Geo::Widgets::IConnectionDrivenWidget;
  using TypeSystem::Gui::CurveTypeWidget;

  auto mainWindow = ComponentManager::create<MainWindow*>("Core.MainWindow");

  auto settingsWidget =
    ComponentManager::create<IConnectionDrivenWidget*>("Widgets.ConnectionDrivenWidget");

  auto curveTypeWidget = new CurveTypeWidget();

  settingsWidget->setEditorWidget(curveTypeWidget);

  mainWindow->toCentralWidget(settingsWidget);
}


void
TypeSystemController::
showUnitsWidget()
{
  using Geo::Core::MainWindow;
  using Geo::Widgets::IConnectionDrivenWidget;
  using TypeSystem::Gui::UnitWidget;

  auto mainWindow = ComponentManager::create<MainWindow*>("Core.MainWindow");

  auto settingsWidget =
    ComponentManager::create<IConnectionDrivenWidget*>("Widgets.ConnectionDrivenWidget");

  // inject widget here
  auto unitWidget = new UnitWidget();

  settingsWidget->setEditorWidget(unitWidget);

  mainWindow->toCentralWidget(settingsWidget);
}


//
}
}
