#include "DatabaseController.hpp"

#include <QtWidgets/QLabel>

#include <Core/MainWindow>

#include <Models/ConnectionsEditorWidgetModel/ConnectionsEditorWidgetModel.hpp>

#include <Gui/ConnectionsEditorWidget/ConnectionsEditorWidget.hpp>
#include <Gui/Traits/TraitsWidget.hpp>

#include <ComponentManager/Creator>

#include <Widgets/ConnectionSettingsWidget>

namespace Geo
{
namespace  Database
{
DatabaseController* DatabaseController::_instance = nullptr;

DatabaseController &
DatabaseController::
instance()
{
  static DatabaseController _instance;

  return _instance;
}


DatabaseController::
DatabaseController()
{
  //
}


DatabaseController::
~DatabaseController()
{
  //
}


void
DatabaseController::
showConnectionsWidget()
{
  using Geo::Core::MainWindow;
  using Geo::Database::Gui::ConnectionsEditorWidget::ConnectionsEditorWidget;
  using Model = Geo::Database::Models::ConnectionsEditorWidgetModel;

  MainWindow* mainWindow =
    ComponentManager::create<MainWindow*>("Core.MainWindow");

  // TODO remove model
  auto databaseConnectionsTreeModel = new Model();

  auto databaseConnectionsWidget = new ConnectionsEditorWidget(databaseConnectionsTreeModel);

  mainWindow->toCentralWidget(databaseConnectionsWidget);
}


void
DatabaseController::
showSettingsWidget()
{
  using Geo::Core::MainWindow;

  auto mainWindow = ComponentManager::create<MainWindow*>("Core.MainWindow");

  auto settingsWidget =
    ComponentManager::create<Geo::Widgets::ConnectionSettingsWidget*>("Widgets.ConnectionSettingsWidget");

  using Geo::Database::Gui::Traits::TraitsWidget;
  auto traitsWidget = new TraitsWidget();

  settingsWidget->setEditorWidget(traitsWidget);

  mainWindow->toCentralWidget(settingsWidget);
}


//
}
}
