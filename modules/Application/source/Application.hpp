#pragma once

#include <memory>

#include <QtWidgets/QApplication>

#include <Core/IMainWindow>

namespace Geo
{

class Application : public QApplication
{
  Q_OBJECT

public:

  Application(int& argc, char** argv);

  virtual
  ~Application();

  void
  createMainWindow();

private:

  using IMainWindow = Core::IMainWindow;

  std::shared_ptr<IMainWindow> _mainWindow;
};
}
