#include "ImportController.hpp"

#include <QAbstractItemModel>
#include <QFileDialog>
#include <QSharedPointer>
#include <QTreeView>
#include <QVector>

#include "ImportTreeModel.hpp"
#include "ImportWidget.hpp"

#include "Las/LasFile.hpp"
#include "Las/LasFileParser.hpp"
#include "Las/TreeWrapper/LasFileEntry.hpp"

#include <DependencyManager/ApplicationContext>
// #include <DependencyManager/XmlApplicationContextLoader>

#include <Core/MainWindow>

#include <Uni/Logging/logging>

using Geo::Import::TreeWrapper::LasFileEntry;

namespace Geo {
namespace Import {
ImportController* ImportController::_instance = nullptr;

ImportController::
ImportController()
{
  //
}


ImportController::
~ImportController()
{
  //
}


ImportController*
ImportController::
instance()
{
  if (!_instance)
    _instance = new ImportController();

  return _instance;
}


void
ImportController::
selectFilesAndImport()
{
  using DependencyManager::ApplicationContext;
  using Geo::Core::MainWindow;

  MainWindow* mainWindow =
    ApplicationContext::create<MainWindow>("Core.MainWindow");

  QStringList fileList =
    QFileDialog::getOpenFileNames(mainWindow,
                                  "Select one or more files to import",
                                  "/home",
                                  "LAS files (*.las)");

  LasFileParser          lasFileParser;
  QVector<LasFileEntry*> importTreeWrapperLasFile;

  // collect list of parsed las files

  for (QString fileName : fileList) {
    QSharedPointer<LasFile> lasFile = lasFileParser.parse(fileName);

    importTreeWrapperLasFile.append(new LasFileEntry(lasFile));
  }

  if (importTreeWrapperLasFile.size() == 0)
    return;

  ImportTreeModel* importTreeModel = new ImportTreeModel(importTreeWrapperLasFile);

  ImportWidget* importWidget = new ImportWidget();

  importWidget->setModel(importTreeModel);

  mainWindow->toCentralWidget(importWidget);
}
}
}
