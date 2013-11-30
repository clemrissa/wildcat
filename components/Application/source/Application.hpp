#ifndef Geo_Application_hpp
#define Geo_Application_hpp

#include "Core/MainWindow"

#include <QApplication>

#include <boost/shared_ptr.hpp>

namespace Geo {
class Application: public QApplication {
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

#endif
