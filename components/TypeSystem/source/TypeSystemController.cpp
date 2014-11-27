#include "TypeSystemController.hpp"

#include <QtWidgets/QLabel>

//#include <Core/MainWindow>
//#include <Uni/Logging/Logging>

//#include <Models/ConnectionsEditorWidgetModel/ConnectionsEditorWidgetModel.hpp>
//#include <Models/DatabaseSettingsWidgetModel/DatabaseSettingsWidgetModel.hpp>

//#include <Gui/ConnectionsEditorWidget/ConnectionsEditorWidget.hpp>
//#include <Gui/DatabaseSettingsWidget/DatabaseSettingsWidget.hpp>

#include <DependencyManager/ApplicationContext>

namespace Geo {
namespace  Database {
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
showConnectionsWidget()
{
  //using DependencyManager::ApplicationContext;
  //using Geo::Core::MainWindow;
  //using Geo::Database::Gui::ConnectionsEditorWidget::ConnectionsEditorWidget;
  //using Model =
          //Geo::Database::Models::ConnectionsEditorWidgetModel::
          //ConnectionsEditorWidgetModel;

  //MainWindow* mainWindow =
    //ApplicationContext::create<MainWindow>("Core.MainWindow");

  //// TODO remove model
  //auto databaseConnectionsTreeModel = new Model();

  //auto databaseConnectionsWidget = new ConnectionsEditorWidget(
    //databaseConnectionsTreeModel);

  //mainWindow->toCentralWidget(databaseConnectionsWidget);
}


void
TypeSystemController::
showSettingsWidget()
{
  //using DependencyManager::ApplicationContext;
  //using Geo::Core::MainWindow;

  //using Geo::Database::Gui::DatabaseSettingsWidget::DatabaseSettingsWidget;
  //using Geo::Database::Models::DatabaseSettingsWidgetModel::
        //DatabaseSettingsWidgetModel;

  //MainWindow* mainWindow =
    //ApplicationContext::create<MainWindow>("Core.MainWindow");

  //auto databaseSettingsWidgetModel =
    //new DatabaseSettingsWidgetModel();

  //auto databaseConnectionsWidget =
    //new DatabaseSettingsWidget(databaseSettingsWidgetModel);

  //mainWindow->toCentralWidget(databaseConnectionsWidget);
}


//
}
}
