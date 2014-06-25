#include "LogViewerController.hpp"

#include <QAbstractItemModel>
#include <QLabel>
#include <QSharedPointer>
#include <QVector>

#include "LogViewerWidget.hpp"

#include <DependencyManager/ApplicationContext>

#include <Core/MainWindow>

#include <Uni/Logging/Logging>

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
  using DependencyManager::ApplicationContext;
  using Geo::Core::MainWindow;

  MainWindow* mainWindow =
    ApplicationContext::create<MainWindow>("Core.MainWindow");

  LogViewerWidget* logviewerWidget = new LogViewerWidget();

  mainWindow->toCentralWidget(logviewerWidget);
}
