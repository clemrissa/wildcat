#include "DatabaseController.hpp"

#include <QtWidgets/QLabel>

#include <Core/MainWindow>

#include "Gui/ConnectionsEditorWidget/ConnectionsEditorWidgetModel.hpp"
#include "Gui/ConnectionsEditorWidget/ConnectionsEditorWidget.hpp"
#include "Gui/Traits/TraitsWidget.hpp"

#include <ComponentManager/Creator>

#include <Widgets/IConnectionDrivenWidget>

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

  // TODO remove model
  auto databaseConnectionsTreeModel = new Model();

  auto databaseConnectionsWidget =
    new ConnectionsEditorWidget(databaseConnectionsTreeModel);

  auto* mainWindow = ComponentManager::create<MainWindow*>("Core.MainWindow");
  mainWindow->toCentralWidget(databaseConnectionsWidget);
}


void
DatabaseController::
showTraitsWidget()
{
  using Geo::Core::MainWindow;
  using Geo::Widgets::IConnectionDrivenWidget;

  auto settingsWidget =
    ComponentManager::create<IConnectionDrivenWidget*>("Widgets.ConnectionDrivenWidget");

  using Geo::Database::Gui::Traits::TraitsWidget;
  auto traitsWidget = new TraitsWidget();

  settingsWidget->setEditorWidget(traitsWidget);

  auto mainWindow = ComponentManager::create<MainWindow*>("Core.MainWindow");
  mainWindow->toCentralWidget(settingsWidget);
}


//
}
}
