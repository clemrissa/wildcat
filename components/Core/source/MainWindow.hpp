#ifndef Geo_Core_MainWindow_hpp
#define Geo_Core_MainWindow_hpp

#include <QtCore/QString>
#include <QtWidgets/QMainWindow>

namespace Geo {
namespace Core {
//

class MainWindow: public QMainWindow
{
public:
  virtual void
  toCentralWidget(QWidget* widget) = 0;

public slots:
  virtual void
  setStatus(QString status) = 0;
};

//
}
}
#endif
