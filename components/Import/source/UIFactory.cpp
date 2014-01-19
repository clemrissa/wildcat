#include "UIFactory.hpp"

#include <QAction>
#include <QIcon>
#include <QList>
#include <QMenu>
#include <QToolBar>

#include "Auxiliary/ExecutionControl.hpp"

namespace Geo {
namespace Import {
class UIFactory::UIFactoryImplementation {
public:
  UIFactoryImplementation():
    _menu(new QMenu()),
    _toolBar(new QToolBar()) {
    //
  }

  void
  fillActionList(UIFactory* uiFactory) {
    QAction* action = nullptr;

    action = new QAction(QIcon(),
                         tr("Import..."),
                         uiFactory);

    // QObject::connect(action, &QAction::changed, this, )

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

UIFactory::
UIFactory():
  _pimpl(new UIFactoryImplementation()) {
  _pimpl->fillActionList(this);
  _pimpl->constructMenu();
  _pimpl->constructToolBar();
}

QMenu*
UIFactory::
getImportMenu() {
  return _pimpl->_menu;
  INFO << "getImportMenu is invoked";
}

QToolBar*
UIFactory::
getImportToolBar() {
  return _pimpl->_toolBar;
}

// implementation of slots

void
UIFactory::
showImportWindow() {
  //
}
}
}
