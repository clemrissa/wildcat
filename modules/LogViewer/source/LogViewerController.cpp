#include "LogViewerController.hpp"

#include <QAbstractItemModel>
#include <QLabel>
#include <QSharedPointer>
#include <QVector>

#include "LogViewerWidget.hpp"

#include <ComponentManager/Creator>

#include <Core/IMainWindow>

using Geo::LogViewer::LogViewerController;
using Geo::LogViewer::LogViewerWidget;


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


LogViewerController&
LogViewerController::
instance()
{
  static LogViewerController instance;

  return instance;
}


void
LogViewerController::
createLogViewer()
{
  using Geo::Core::IMainWindow;

  IMainWindow* mainWindow =
    ComponentManager::create<IMainWindow*>("Core.MainWindow");

  LogViewerWidget* logviewerWidget = new LogViewerWidget();

  mainWindow->toCentralWidget(logviewerWidget);
}
