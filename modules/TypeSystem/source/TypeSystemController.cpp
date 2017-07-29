#include "TypeSystemController.hpp"

#include <QtWidgets/QLabel>

#include <Core/MainWindow>
#include <ComponentManager/Creator>

#include <Widgets/IConnectionSettingsWidget>

#include "Gui/CurveTypes/CurveTypeWidget.hpp"
#include "Gui/Units/UnitWidget.hpp"

namespace Geo
{
namespace TypeSystem
{
//

TypeSystemController* TypeSystemController::_instance = nullptr;

TypeSystemController*
TypeSystemController::
instance()
{
  if (!_instance)
    _instance = new TypeSystemController();

  return _instance;
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
  using Geo::Widgets::IConnectionSettingsWidget;
  using TypeSystem::Gui::CurveTypeWidget;

  auto mainWindow = ComponentManager::create<MainWindow*>("Core.MainWindow");

  auto settingsWidget =
    ComponentManager::create<IConnectionSettingsWidget*>("Widgets.ConnectionSettingsWidget");

  auto curveTypeWidget = new CurveTypeWidget();

  settingsWidget->setEditorWidget(curveTypeWidget);

  mainWindow->toCentralWidget(settingsWidget);
}


void
TypeSystemController::
showUnitsWidget()
{
  using Geo::Core::MainWindow;
  using Geo::Widgets::IConnectionSettingsWidget;
  using TypeSystem::Gui::UnitWidget;

  auto mainWindow = ComponentManager::create<MainWindow*>("Core.MainWindow");

  auto settingsWidget =
    ComponentManager::create<IConnectionSettingsWidget*>("Widgets.ConnectionSettingsWidget");

  // inject widget here
  auto unitWidget = new UnitWidget();

  settingsWidget->setEditorWidget(unitWidget);

  mainWindow->toCentralWidget(settingsWidget);
}


//
}
}
