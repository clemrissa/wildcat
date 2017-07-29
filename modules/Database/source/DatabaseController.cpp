#include "DatabaseController.hpp"

#include <QtWidgets/QLabel>

#include <Core/MainWindow>

#include "Gui/ConnectionsEditorWidget/ConnectionsEditorWidgetModel.hpp"
#include "Gui/ConnectionsEditorWidget/ConnectionsEditorWidget.hpp"
#include "Gui/Traits/TraitsWidget.hpp"

#include <ComponentManager/Creator>

#include <Widgets/IConnectionSettingsWidget>

namespace Geo
{
namespace  Database
{

DatabaseController &
DatabaseController::
instance()
{
  static DatabaseController instance;

  return instance;
}


void
DatabaseController::
showConnectionsWidget()
{
  using Geo::Core::MainWindow;
  using Geo::Database::Gui::ConnectionsEditorWidget::ConnectionsEditorWidget;
  using Model = Geo::Database::Gui::ConnectionsEditorWidgetModel;

  MainWindow* mainWindow =
    ComponentManager::create<MainWindow*>("Core.MainWindow");

  // TODO remove model
  auto databaseConnectionsTreeModel = new Model();

  auto databaseConnectionsWidget =
    new ConnectionsEditorWidget(databaseConnectionsTreeModel);

  mainWindow->toCentralWidget(databaseConnectionsWidget);
}


void
DatabaseController::
showSettingsWidget()
{
  using Geo::Core::MainWindow;

  auto mainWindow = ComponentManager::create<MainWindow*>("Core.MainWindow");

  auto settingsWidget =
    ComponentManager::create<Geo::Widgets::IConnectionSettingsWidget*>("Widgets.ConnectionSettingsWidget");

  using Geo::Database::Gui::Traits::TraitsWidget;
  auto traitsWidget = new TraitsWidget();

  settingsWidget->setEditorWidget(traitsWidget);

  mainWindow->toCentralWidget(settingsWidget);
}


//
}
}
