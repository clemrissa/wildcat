#ifndef Geo_Core_Private_BasicMainWindow_hpp
#define Geo_Core_Private_BasicMainWindow_hpp

#include <MainWindow.hpp>

#include <QDockWidget>
#include <QMenu>

class QMdiArea;
class QMenu;
class QToolBar;

namespace Geo {
namespace Core {
namespace Private {
class BasicMainWindow: public Geo::Core::MainWindow {
  Q_OBJECT

public:
  Q_INVOKABLE
  BasicMainWindow();

  virtual
  ~BasicMainWindow();

  Q_INVOKABLE void
  toBottomDock(QDockWidget* dockWidget);

  Q_INVOKABLE void
  toLeftDock(QDockWidget* dockWidget);

  Q_INVOKABLE void
  toRightDock(QDockWidget* dockWidget);

  Q_INVOKABLE void
  toCentralWidget(QWidget* widget);

  // -----

  Q_INVOKABLE void
  addMenu(QMenu* menu);

  Q_INVOKABLE void
  addToolBar(QToolBar* toolBar);

private:
  QMdiArea* _mdiArea;
};
}
}
}
#endif
