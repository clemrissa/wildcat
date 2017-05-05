#include "TypeSystemController.hpp"

#include <QtWidgets/QLabel>

#include <Core/MainWindow>
#include <DependencyManager/ApplicationContext>

#include <Widgets/ConnectionSettingsWidget>

#include "Gui/CurveTypes/CurveTypeWidget.hpp"
#include "Gui/Units/UnitWidget.hpp"

namespace Geo {
namespace TypeSystem {
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
  using AC = DependencyManager::ApplicationContext;
  using Geo::Core::MainWindow;
  using Geo::Widgets::ConnectionSettingsWidget;
  using TypeSystem::Gui::CurveTypeWidget;

  auto mainWindow = AC::create<MainWindow>("Core.MainWindow");

  auto settingsWidget =
    AC::create<ConnectionSettingsWidget>("Widgets.ConnectionSettingsWidget");

  auto curveTypeWidget = new CurveTypeWidget();

  settingsWidget->setEditorWidget(curveTypeWidget);

  mainWindow->toCentralWidget(settingsWidget);
}


void
TypeSystemController::
showUnitsWidget()
{
  using AC = DependencyManager::ApplicationContext;
  using Geo::Core::MainWindow;
  using Geo::Widgets::ConnectionSettingsWidget;
  using TypeSystem::Gui::UnitWidget;

  auto mainWindow = AC::create<MainWindow>("Core.MainWindow");

  auto settingsWidget =
    AC::create<ConnectionSettingsWidget>("Widgets.ConnectionSettingsWidget");

  // inject widget here
  auto unitWidget = new UnitWidget();

  settingsWidget->setEditorWidget(unitWidget);

  mainWindow->toCentralWidget(settingsWidget);
}


//
}
}
