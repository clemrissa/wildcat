#ifndef Geo_Core_Private_BasicMainWindow_hpp
#define Geo_Core_Private_BasicMainWindow_hpp

#include <MainWindow.hpp>

#include <QDockWidget>

class QMdiArea;

namespace Geo {
namespace Core {
namespace Private {
class BasicMainWindow : public Geo::Core::MainWindow {
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

private:
  QMdiArea* _mdiArea;
};
}
}
}
#endif
