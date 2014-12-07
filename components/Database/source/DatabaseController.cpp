#include "DatabaseController.hpp"

#include <QtWidgets/QLabel>

#include <Core/MainWindow>
#include <Uni/Logging/Logging>

#include <Models/ConnectionsEditorWidgetModel/ConnectionsEditorWidgetModel.hpp>

#include <Gui/ConnectionsEditorWidget/ConnectionsEditorWidget.hpp>
#include <Gui/Traits/TraitsWidget.hpp>

#include <DependencyManager/ApplicationContext>

#include <Widgets/ConnectionSettingsWidget>

namespace Geo {
namespace  Database {
DatabaseController* DatabaseController::_instance = nullptr;

DatabaseController*
DatabaseController::
instance()
{
  if (!_instance)
    _instance = new DatabaseController();

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
  using DependencyManager::ApplicationContext;
  using Geo::Core::MainWindow;
  using Geo::Database::Gui::ConnectionsEditorWidget::ConnectionsEditorWidget;
  using Model = Geo::Database::Models::ConnectionsEditorWidgetModel::
                ConnectionsEditorWidgetModel;

  MainWindow* mainWindow =
    ApplicationContext::create<MainWindow>("Core.MainWindow");

  // TODO remove model
  auto databaseConnectionsTreeModel = new Model();

  auto databaseConnectionsWidget = new ConnectionsEditorWidget(
    databaseConnectionsTreeModel);

  mainWindow->toCentralWidget(databaseConnectionsWidget);
}


void
DatabaseController::
showSettingsWidget()
{
  using AC = DependencyManager::ApplicationContext;
  using Geo::Core::MainWindow;

  auto mainWindow = AC::create<MainWindow>("Core.MainWindow");

  auto settingsWidget =
    AC::create<Geo::Widgets::ConnectionSettingsWidget>(
      "Widgets.ConnectionSettingsWidget");

  using Geo::Database::Gui::Traits::TraitsWidget;
  auto traitsWidget = new TraitsWidget();

  settingsWidget->setEditorWidget(traitsWidget);

  mainWindow->toCentralWidget(settingsWidget);
}


//
}
}
