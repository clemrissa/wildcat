#ifndef _Geo_Import_ImportUiFactory_h_
#define _Geo_Import_ImportUiFactory_h_

#include <QObject>

class QMenu;
class QToolBar;

namespace Geo {
namespace Import {
// Creates menu and tool bar for using import component
class ImportUiFactory: public QObject {
  Q_OBJECT

public:
  Q_INVOKABLE
  ImportUiFactory();

  virtual
  ~ImportUiFactory();

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
  class ImportUiFactoryImplementation;
  ImportUiFactoryImplementation* _pimpl;
};
}
}

#endif // _Geo_Import_ImportUiFactory_h_
