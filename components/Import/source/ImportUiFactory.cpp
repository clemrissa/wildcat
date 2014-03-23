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
    _menu(new QMenu(tr("Import"))),
    _toolBar(new QToolBar()) {
    //
  }

  void
  fillActionList(ImportUiFactory* uiFactory) {
    using DependencyManager::ApplicationContext;
    using Geo::Core::MainWindow;

    MainWindow* mainWindow =
      DependencyManager::ApplicationContext::create<MainWindow>("Core.MainWindow");

    QAction* action = nullptr;

    action = new QAction(QIcon(), QString("Las Files"), mainWindow);

    connect(action,
            &QAction::triggered,
            ImportController::instance(),
            &ImportController::selectFilesAndImport);

    _actionList.append(action);
  }

  void
  constructMenu() {
    for (QAction* action : _actionList)
      _menu->addAction(action);
  }

  void
  constructToolBar() {
    for (QAction* action : _actionList)
      _toolBar->addAction(action);
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
  // _pimpl->constructToolBar();
}

ImportUiFactory::~ImportUiFactory() {
  delete _pimpl;
}

Q_INVOKABLE QMenu*
ImportUiFactory::
getImportMenu() {
  return _pimpl->_menu;
}

Q_INVOKABLE QToolBar*
ImportUiFactory::
getImportToolBar() {
  return _pimpl->_toolBar;
}
}
}
