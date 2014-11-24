#include "ImportController.hpp"

#include <QAbstractItemModel>
#include <QFileDialog>
#include <QSharedPointer>
#include <QTreeView>
#include <QVector>

#include "ImportTreeModel.hpp"

#include <Gui/ImportWidget.hpp>

#include "Las/LasFile.hpp"
#include "Las/LasFileParser.hpp"
#include "Las/TreeWrapper/LasFileEntry.hpp"

#include <DependencyManager/ApplicationContext>

#include <Core/MainWindow>

#include <Uni/Logging/Logging>

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

  LasFileParser            lasFileParser;
  QVector<LasFile::Shared> lasFiles;

  // collect a list of parsed las files
  for (QString fileName : fileList) {
    LasFile::Shared lasFile = lasFileParser.parse(fileName);
    lasFiles.append(lasFile);
  }

  if (lasFiles.size() == 0)
    return;

  ImportTreeModel* importTreeModel =
    new ImportTreeModel(lasFiles);

  using Geo::Import::Gui::ImportWidget;

  ImportWidget* importWidget = new ImportWidget();

  importWidget->setModel(importTreeModel);

  mainWindow->toCentralWidget(importWidget);
}
}
}
