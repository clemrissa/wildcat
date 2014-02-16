#include "ImportController.hpp"

#include <QAbstractItemModel>
#include <QFileDialog>
#include <QTreeView>
#include <QVector>

#include "ImportTreeLasFileModel.hpp"
#include "ImportTreeModel.hpp"
#include "LasFile.hpp"
#include "LasFileParser.hpp"

#include <DependencyManager/ApplicationContext>
#include <DependencyManager/XmlApplicationContextLoader>

#include <Core/MainWindow>

#include <Uni/Logging/Logging>

namespace Geo {
namespace Import {
ImportController* ImportController::_instance = nullptr;

ImportController::
ImportController() {
  INFO << "Hello from constructor of ImportController";
}

ImportController::
~ImportController() {
  //
}

ImportController*
ImportController::
instance() {
  if (!_instance)
    _instance = new ImportController();

  return _instance;

  INFO << "Getting instance";
}

void
ImportController::
selectFilesAndImport() {
  using       Geo::Core::MainWindow;
  MainWindow* mainWindow =
    DependencyManager::ApplicationContext::create<MainWindow>("Core.MainWindow");

  QStringList fileList =
    QFileDialog::getOpenFileNames(mainWindow,
                                  "Select one or more files to import",
                                  "/home",
                                  "LAS files (*.las)");

  LasFileParser                    lasFileParser;
  QVector<ImportTreeLasFileModel*> importTreeLasFileModels;

  // collect list of parsed las files
  for (QString fileName : fileList)
    importTreeLasFileModels.append(new
                                   ImportTreeLasFileModel(lasFileParser.parse(fileName)));

  ImportTreeModel* importTreeModel = new
                                     ImportTreeModel(importTreeLasFileModels);

  // create TreeView which will show imported las-files
  QTreeView* treeView = new QTreeView();

  treeView->setModel(importTreeModel);

  mainWindow->toCentralWidget(treeView);
}
}
}
