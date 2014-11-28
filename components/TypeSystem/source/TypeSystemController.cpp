#include "TypeSystemController.hpp"

#include <QtWidgets/QLabel>

// #include <Core/MainWindow>
// #include <Uni/Logging/Logging>

// #include
// <Models/ConnectionsEditorWidgetModel/ConnectionsEditorWidgetModel.hpp>
// #include
// <Models/TypeSystemSettingsWidgetModel/TypeSystemSettingsWidgetModel.hpp>

#include <Core/MainWindow>
#include <DependencyManager/ApplicationContext>

#include <Gui/CurveTypeWidget.hpp>

#include <DependencyManager/ApplicationContext>

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
  using TypeSystem::Gui::CurveTypeWidget;

  auto mainWindow = AC::create<MainWindow>("Core.MainWindow");

  auto curveTypeWidget = new CurveTypeWidget();

  mainWindow->toCentralWidget(curveTypeWidget);
}


//
}
}
