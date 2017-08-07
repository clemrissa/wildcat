#include "DatabaseController.hpp"

#include <QtWidgets/QLabel>

#include <Core/IMainWindow>

#include "Gui/ConnectionsEditorWidget/ConnectionsEditorWidgetModel.hpp"
#include "Gui/ConnectionsEditorWidget/ConnectionsEditorWidget.hpp"
#include "Gui/Traits/TraitsWidget.hpp"

#include <Widgets/IConnectionDrivenWidget>

#include <ComponentManager/Creator>

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
  using Geo::Core::IMainWindow;
  using Geo::Database::Gui::ConnectionsEditorWidget::ConnectionsEditorWidget;
  using Model = Geo::Database::Gui::ConnectionsEditorWidgetModel;

  // TODO remove model
  auto databaseConnectionsTreeModel = new Model();

  auto databaseConnectionsWidget =
    new ConnectionsEditorWidget(databaseConnectionsTreeModel);

  auto* mainWindow = ComponentManager::create<IMainWindow*>("Core.MainWindow");
  mainWindow->toCentralWidget(databaseConnectionsWidget);
}


void
DatabaseController::
showTraitsWidget()
{
  using Geo::Core::IMainWindow;
  using Geo::Widgets::IConnectionDrivenWidget;

  auto settingsWidget =
    ComponentManager::create<IConnectionDrivenWidget*>("Widgets.ConnectionDrivenWidget");

  using Geo::Database::Gui::TraitsWidget;
  auto traitsWidget = new TraitsWidget();

  settingsWidget->setEditorWidget(traitsWidget);

  auto mainWindow = ComponentManager::create<IMainWindow*>("Core.MainWindow");
  mainWindow->toCentralWidget(settingsWidget);
}


//
}
}
