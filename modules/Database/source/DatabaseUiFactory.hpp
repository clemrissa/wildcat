#pragma once

#include <vector>

#include <QtCore/QObject>
#include <QtWidgets/QWidget>

#include "DatabaseExport.hpp"

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
class Database_PUBLIC DatabaseUiFactory : public QObject
{
  Q_OBJECT

public:
  Q_INVOKABLE
  DatabaseUiFactory();

  virtual
  ~DatabaseUiFactory();

  /// Factory method called from json
  Q_INVOKABLE
  QMenu*
  databaseMenu() const;

  /// Called from json
  Q_INVOKABLE
  QToolBar*
  createDatabaseToolBar();

private:

  void
  createDatabaseMenu();

  std::vector<QAction*>
  createActionList() const;

private:

  QMenu *_databaseMenu = nullptr;
};
}
}
