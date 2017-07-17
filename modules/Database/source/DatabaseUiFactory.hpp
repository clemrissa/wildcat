#pragma once

#include <vector>

#include <QtCore/QObject>

#include <QtWidgets/QWidget>

class QMenu;
class QToolBar;

namespace Geo
{
namespace Database
{

/// Creates some UI elements, links them to Core.MainWindow
/**
 * The class is described in Database component's json document.
 * The class functions `createDatabaseMenu` and `createDatabaseToolBar`
 * are called automatically after json processing.
 */
class DatabaseUiFactory : public QObject
{
  Q_OBJECT

public:
  Q_INVOKABLE
  DatabaseUiFactory();

  virtual
  ~DatabaseUiFactory();

  /// Called from json
  Q_INVOKABLE
  QMenu*
  createDatabaseMenu();

  /// Called from json
  Q_INVOKABLE
  QToolBar*
  createDatabaseToolBar();

private:

  std::vector<QAction*>
  createActionList() const;
};
}
}
