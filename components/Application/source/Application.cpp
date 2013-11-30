#include "Application.hpp"

#include <DependencyManager/ApplicationContext>

// --

using namespace Geo;

Application::
Application(int& argc, char** argv): QApplication(argc, argv) {
  // INFO << "Application was started";
}

Application::
~Application() {
  // INFO << "Application was finished";
}

void
Application::
createMainWindow() {
  MainWindow* mainWindow =
    DependencyManager::ApplicationContext::create<MainWindow>("Core.MainWindow");
  _mainWindow = SharedMainWindow(mainWindow);
  _mainWindow->showMaximized();
}
