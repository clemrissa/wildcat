#ifndef Geo_Database_ConnectionListViewFactory_hpp
#define Geo_Database_ConnectionListViewFactory_hpp

#include "Connection.hpp"

#include <QObject>

#include <QWidget>

#include <QQmlContext>
#include <QQmlEngine>
#include <QQuickView>
#include <QtQml>

class QDockWidget;

namespace Geo {
namespace Database {
namespace Private {
class DatabaseUiFactory: public QObject {
  Q_OBJECT

public:
  Q_INVOKABLE
  DatabaseUiFactory();

  virtual
  ~DatabaseUiFactory();

  Q_INVOKABLE QDockWidget*
  createConnectionListView(QObject* value) const;
};
}
}
}

#endif
