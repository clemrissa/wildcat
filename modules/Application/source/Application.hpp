#pragma once

#include "Core/MainWindow"

#include <QtWidgets/QApplication>

#include <boost/shared_ptr.hpp>

namespace Geo
{

class Application : public QApplication
{
  Q_OBJECT

private:
  typedef Core::MainWindow MainWindow;
  typedef boost::shared_ptr<MainWindow> SharedMainWindow;

public:
  Application(int& argc, char** argv);

  virtual
  ~Application();

  void
  createMainWindow();

private:
  SharedMainWindow _mainWindow;
};
}
