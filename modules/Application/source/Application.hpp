#pragma once

#include <QtWidgets/QApplication>

#include <Core/MainWindow>

#include <memory>

namespace Geo
{

class Application : public QApplication
{
  Q_OBJECT

private:

  using MainWindow = Core::MainWindow;

public:
  Application(int& argc, char** argv);

  virtual
  ~Application();

  void
  createMainWindow();

private:

  std::shared_ptr<MainWindow> _mainWindow;
};
}
