#include "DatabaseController.hpp"

#include <QLabel>

#include <Core/MainWindow>
#include <Uni/Logging/Logging>

#include "DatabaseSettingsTreeModel.hpp"
#include "DatabaseSettingsWidget.hpp"

#include <DependencyManager/ApplicationContext>

namespace Geo {
namespace  Database {
DatabaseController* DatabaseController::_instance = nullptr;

DatabaseController*
DatabaseController::
instance() {
  if (!_instance)
    _instance = new DatabaseController();

  return _instance;
}

DatabaseController::
DatabaseController() {
  //
}

DatabaseController::
~DatabaseController() {
  //
}

void
DatabaseController::
showDatabaseSettingsWidget() {
  using Geo::Core::MainWindow;

  MainWindow* mainWindow =
    DependencyManager::ApplicationContext::create<MainWindow>("Core.MainWindow");

  auto databaseSettingsTreeModel = new DatabaseSettingsTreeModel();

  auto databaseSettingsWidget = new DatabaseSettingsWidget(databaseSettingsTreeModel);

  mainWindow->toCentralWidget(databaseSettingsWidget);
}
}
}
