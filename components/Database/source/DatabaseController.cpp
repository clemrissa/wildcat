#include "DatabaseController.hpp"

#include <QLabel>

#include <Core/MainWindow>
#include <Uni/Logging/Logging>

#include "Gui/SettingsWidget.hpp"
#include "SettingsTreeModel.hpp"

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
showSettingsWidget()
{
  using Geo::Core::MainWindow;
  using Geo::Database::Gui::SettingsWidget;

  MainWindow* mainWindow =
    DependencyManager::ApplicationContext::create<MainWindow>("Core.MainWindow");

  auto databaseSettingsTreeModel = new SettingsTreeModel();

  auto databaseSettingsWidget = new SettingsWidget(databaseSettingsTreeModel);

  mainWindow->toCentralWidget(databaseSettingsWidget);
}
}
}
