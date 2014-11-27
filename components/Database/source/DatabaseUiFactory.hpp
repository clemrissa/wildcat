#ifndef Geo_Database_DatabaseUiFactory_hpp
#define Geo_Database_DatabaseUiFactory_hpp

#include <QObject>
#include <QWidget>

class QMenu;
class QToolBar;

namespace Geo {
namespace Database {
//

/// Creates some UI elements, links them to
class DatabaseUiFactory: public QObject
{
  Q_OBJECT

public:
  Q_INVOKABLE
  DatabaseUiFactory();

  virtual
  ~DatabaseUiFactory();

  Q_INVOKABLE
  QMenu*
  createDatabaseMenu();

  Q_INVOKABLE
  QToolBar*
  createDatabaseToolBar();

private:
  QList<QAction*>
  createActionList() const;
};
}
}

#endif
