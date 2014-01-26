#include "ImportUiFactory.hpp"

#include <QAction>
#include <QIcon>
#include <QList>
#include <QMenu>
#include <QToolBar>

#include "Auxiliary/ExecutionControl.hpp"

#include "ImportController.hpp"

namespace Geo {
namespace Import {
class ImportUiFactory::ImportUiFactoryImplementation {
public:
  ImportUiFactoryImplementation():
    _menu(new QMenu()),
    _toolBar(new QToolBar()) {
    //
  }

  void
  fillActionList(ImportUiFactory* uiFactory) {
    QAction* action = nullptr;

    action = new QAction(QIcon(), tr("Import..."), uiFactory);

    connect(action, &QAction::changed,
            ImportController::instance(),
            &ImportController::selectFilesAndImport);

    _actionList.append(action);
  }

  void
  constructMenu() {
    for (QAction* action : _actionList)
      _menu->addAction(action);

    INFO << "Menu constructed";
  }

  void
  constructToolBar() {
    for (QAction* action : _actionList)
      _toolBar->addAction(action);

    INFO << "ToolBar constructed";
  }

public:
  QMenu*    _menu;
  QToolBar* _toolBar;

  QList<QAction*> _actionList;
};

// --------------------------------------------------

Q_INVOKABLE
ImportUiFactory::
ImportUiFactory():
  _pimpl(new ImportUiFactoryImplementation()) {
  _pimpl->fillActionList(this);
  _pimpl->constructMenu();
  _pimpl->constructToolBar();
}

ImportUiFactory::~ImportUiFactory() {
  delete _pimpl;
}

Q_INVOKABLE QMenu*
ImportUiFactory::
getImportMenu() {
  // return _pimpl->_menu;
  return 0;
  INFO << "getImportMenu is invoked";
}

Q_INVOKABLE QToolBar*
ImportUiFactory::
getImportToolBar() {
  // return _pimpl->_toolBar;
  return 0;
}

// implementation of slots

void
ImportUiFactory::
showImportWindow() {
  //
}
}
}
