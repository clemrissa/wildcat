#ifndef Geo_Database_TypeSystemUiFactory_hpp
#define Geo_Database_TypeSystemUiFactory_hpp

#include <QObject>
#include <QWidget>

class QMenu;
class QToolBar;

namespace Geo {
namespace TypeSystem {
//

/// Creates some UI elements, links them to
class TypeSystemUiFactory: public QObject
{
  Q_OBJECT

public:
  Q_INVOKABLE
  TypeSystemUiFactory();

  virtual
  ~TypeSystemUiFactory();

  Q_INVOKABLE QMenu*
  createTypeSystemMenu();

  Q_INVOKABLE
  QToolBar*
  createTypeSystemToolBar();

private:
  QList<QAction*>
  createActionList() const;
};
}
}

#endif
