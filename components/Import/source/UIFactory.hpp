#ifndef _Geo_Import_UIFactory_h_
#define _Geo_Import_UIFactory_h_

#include <QObject>

class QMenu;
class QToolBar;

namespace Geo {
namespace Import {
// Creates menu and tool bar for using import component
class UIFactory: public QObject {
  Q_OBJECT

public:
  Q_INVOKABLE
  UIFactory();

  virtual
  ~UIFactory() {}

  Q_INVOKABLE
  QMenu*
  getImportMenu();

  Q_INVOKABLE
  QToolBar*
  getImportToolBar();

public slots:
  void
  showImportWindow();

private:
  class UIFactoryImplementation;
  UIFactoryImplementation* _pimpl;
};
}
}

#endif // _Geo_Import_UIFactory_h_
