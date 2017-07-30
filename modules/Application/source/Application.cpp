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
  // INFO << "Application was finished";
}


void
Application::
createMainWindow()
{
  MainWindow* mainWindow =
    ComponentManager::create<MainWindow*>("Core.MainWindow");

  _mainWindow = std::shared_ptr<MainWindow>(mainWindow);
  _mainWindow->showMaximized();
}


//
}
