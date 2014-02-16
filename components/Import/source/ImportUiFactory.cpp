#include "ImportUiFactory.hpp"

#include <QAction>
#include <QIcon>
#include <QList>
#include <QMenu>
#include <QToolBar>

#include <Core/MainWindow>

#include <DependencyManager/ApplicationContext>
#include <DependencyManager/XmlApplicationContextLoader>

#include <Uni/Logging/Logging>

#include "ImportController.hpp"

namespace Geo {
namespace Import {
class ImportUiFactory::ImportUiFactoryImplementation {
public:
  ImportUiFactoryImplementation():
    _menu(new QMenu(tr("Menu"))),
    _toolBar(new QToolBar()) {
    //
  }

  void
  fillActionList(ImportUiFactory* uiFactory) {
    // using       Geo::Core::MainWindow;
    // MainWindow* mainWindow =
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    // DependencyManager::ApplicationContext::create<MainWindow>("Core.MainWindow");

    // MainWindow* mainWindow2 =
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    // DependencyManager::ApplicationContext::create<MainWindow>("Core.MainWindow");

    // Q_ASSERT(mainWindow == mainWindow2);

    // QAction* action = nullptr;

    //// action = new QAction(QIcon(), tr("Import..."), uiFactory);
    // action = new QAction(QIcon(), QString("Import..."), mainWindow);

    //// connect(action, &QAction::changed,
    //// ImportController::instance(),
    //// &ImportController::selectFilesAndImport);

    // INFO << "ooo Action list filled";

    // _actionList.append(action);
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

    INFO << "ooo ToolBar constructed";
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
  INFO << "ooo Import UI factory constructed";
}

ImportUiFactory::~ImportUiFactory() {
  delete _pimpl;
}

Q_INVOKABLE QMenu*
ImportUiFactory::
getImportMenu() {
  return _pimpl->_menu;

  INFO << "getImportMenu is invoked";
}

Q_INVOKABLE QToolBar*
ImportUiFactory::
getImportToolBar() {
  return _pimpl->_toolBar;
  INFO << "getImportToolBar is invoked";
}

// implementation of slots

void
ImportUiFactory::
showImportWindow() {
  //
}
}
}
