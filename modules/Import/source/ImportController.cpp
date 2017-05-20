#include "ImportController.hpp"

#include <QtCore/QAbstractItemModel>
#include <QtWidgets/QFileDialog>

#include <QtWidgets/QTreeView>

#include "ImportTreeModel.hpp"

#include <Gui/ImportWidget.hpp>

#include "Las/LasFile.hpp"
#include "Las/LasFileParser.hpp"
#include "Las/TreeWrapper/LasFileEntry.hpp"

#include <ComponentManager/Creator>

#include <Core/MainWindow>

using Geo::Import::TreeWrapper::LasFileEntry;

namespace Geo {
namespace Import {
//

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
  using       Geo::Core::MainWindow;
  MainWindow* mainWindow = ComponentManager::create<MainWindow*>("Core.MainWindow");

  QStringList fileList =
    QFileDialog::getOpenFileNames(mainWindow,
                                  "Select one or more files to import",
                                  "/home",
                                  "LAS files (*.las)");

  LasFileParser lasFileParser;
  std::vector<LasFile::Shared> lasFiles;

  // collect a list of parsed las files
  for (QString fileName : fileList)
  {
    LasFile::Shared lasFile = lasFileParser.parse(fileName);
    lasFiles.push_back(lasFile);
  }

  if (lasFiles.size() == 0)
    return;

  ImportTreeModel* importTreeModel = new ImportTreeModel(lasFiles);

  using Geo::Import::Gui::ImportWidget;

  ImportWidget* importWidget = new ImportWidget();

  importWidget->setModel(importTreeModel);

  mainWindow->toCentralWidget(importWidget);
}
}
}
