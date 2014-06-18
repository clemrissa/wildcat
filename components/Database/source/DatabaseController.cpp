#include "DatabaseController.hpp"

#include <QLabel>

#include <Core/MainWindow>
#include <Uni/Logging/Logging>

#include <Models/ConnectionsWidgetModel/ConnectionsWidgetModel.hpp>
#include <Models/SettingsWidgetModel/SettingsWidgetModel.hpp>

#include <Gui/ConnectionsWidget.hpp>
#include <Gui/SettingsWidget.hpp>

#include <DependencyManager/ApplicationContext>

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
  using Geo::Database::Gui::ConnectionsWidget;
  using Model = Geo::Database::Models::ConnectionsWidgetModel::ConnectionsWidgetModel;

  MainWindow* mainWindow =
    ApplicationContext::create<MainWindow>("Core.MainWindow");

  auto databaseConnectionsTreeModel = new Model();

  auto databaseConnectionsWidget = new ConnectionsWidget(databaseConnectionsTreeModel);

  mainWindow->toCentralWidget(databaseConnectionsWidget);
}


void
DatabaseController::
showSettingsWidget()
{
  using DependencyManager::ApplicationContext;
  using Geo::Core::MainWindow;

  using Geo::Database::Gui::SettingsWidget;
  using Geo::Database::Models::SettingsWidgetModel::SettingsWidgetModel;

  MainWindow* mainWindow =
    ApplicationContext::create<MainWindow>("Core.MainWindow");

  auto databaseSettingsWidgetModel = new SettingsWidgetModel();

  auto databaseConnectionsWidget = new SettingsWidget(databaseSettingsWidgetModel);

  mainWindow->toCentralWidget(databaseConnectionsWidget);
}


//
}
}
