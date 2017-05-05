#ifndef Geo_Import_ImportUiFactory_hpp
#define Geo_Import_ImportUiFactory_hpp

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

public:
  Q_INVOKABLE
  QMenu*
  getImportMenu();

  Q_INVOKABLE
  QToolBar*
  getImportToolBar();

private:
  class Private;
  Private* _p;
};
}
}

#endif // Geo_Import_ImportUiFactory_hpp
