#include "LogViewerController.hpp"

#include <QAbstractItemModel>
#include <QLabel>
#include <QSharedPointer>
#include <QVector>

#include "LogViewerWidget.hpp"

#include <ComponentManager/Creator>

#include <Core/MainWindow>

using Geo::LogViewer::LogViewerController;
using Geo::LogViewer::LogViewerWidget;

LogViewerController* LogViewerController::_instance = nullptr;

LogViewerController::
LogViewerController()
{
  //
}


LogViewerController::
~LogViewerController()
{
  //
}


LogViewerController*
LogViewerController::
instance()
{
  if (!_instance)
    _instance = new LogViewerController();

  return _instance;
}


void
LogViewerController::
createLogViewer()
{
  using Geo::Core::MainWindow;

  MainWindow* mainWindow =
    ComponentManager::create<MainWindow*>("BasicMainWindow");

  LogViewerWidget* logviewerWidget = new LogViewerWidget();

  mainWindow->toCentralWidget(logviewerWidget);
}
