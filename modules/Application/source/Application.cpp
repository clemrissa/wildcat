#include "Application.hpp"

#include <ComponentManager/Creator>

namespace Geo
{

Application::
Application(int& argc, char** argv)
  : QApplication(argc, argv)
{
  qInfo("Application was started");
}


Application::
~Application()
{
  qInfo("Application was finished");
}


void
Application::
createMainWindow()
{
  IMainWindow* mainWindow =
    ComponentManager::create<IMainWindow*>("Core.MainWindow");

  _mainWindow = std::shared_ptr<IMainWindow>(mainWindow);
  _mainWindow->showMaximized();
}


//
}
