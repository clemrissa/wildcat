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

#include <vector>

using Geo::Import::TreeWrapper::LasFileEntry;

namespace Geo
{
namespace Import
{
//


ImportController&
ImportController::
instance()
{
  static ImportController instance;

  return instance;
}


void
ImportController::
selectFilesAndImport()
{
  using       Geo::Core::MainWindow;
  MainWindow* mainWindow = ComponentManager::create<MainWindow*>("Core.MainWindow");

  std::vector<QString> fileList =
    QFileDialog::getOpenFileNames(mainWindow,
                                  "Select one or more files to import",
                                  "/home",
                                  "LAS files (*.las)").toVector().toStdVector();

  std::vector<std::shared_ptr<LasFile>> lasFiles;

  // collect a list of parsed las files
  #pragma omp parallel
  {
    #pragma omp single
    for (std::size_t i = 0; i < fileList.size(); ++i)
    {
      #pragma omp task shared(lasFiles)
      {
        QString & fileName = fileList[i];

        LasFileParser lasFileParser;
        auto lasFile = lasFileParser.parse(fileName);

        #pragma omp critical
        lasFiles.push_back(lasFile);
      }
    }
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
