#include "Application.hpp"

#include <ComponentManager/Creator>

// --

using namespace Geo;

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

  _mainWindow = SharedMainWindow(mainWindow);
  _mainWindow->showMaximized();
}
