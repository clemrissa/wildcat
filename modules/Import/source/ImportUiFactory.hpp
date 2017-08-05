#pragma once

#include <memory>

#include <QtCore/QObject>

class QMenu;
class QToolBar;

namespace Geo
{
namespace Import
{

// Creates menu and tool bar for using import component
class ImportUiFactory : public QObject
{
  Q_OBJECT

public:
  Q_INVOKABLE
  ImportUiFactory();

  virtual
  ~ImportUiFactory();

public:

  Q_INVOKABLE
  QObject*
  getImportMenu();

  Q_INVOKABLE
  QToolBar*
  getImportToolBar();

private:
  class Private;

  std::unique_ptr<Private> _p;
};

//
}
}
