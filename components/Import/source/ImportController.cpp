#include "ImportController.hpp"

#include <QAbstractItemModel>
#include <QFileDialog>
#include <QSharedPointer>
#include <QTreeView>
#include <QVector>

#include "ImportTreeLasFileModel.hpp"
#include "ImportTreeModel.hpp"
#include "LasFile.hpp"
#include "LasFileParser.hpp"

#include <DependencyManager/ApplicationContext>
#include <DependencyManager/XmlApplicationContextLoader>

#include <Core/MainWindow>

#include <Uni/Logging/logging>

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

  INFO << "Getting instance";

  return _instance;
}

QVector<ImportTreeLasFileModel*>
ImportController::
selectFilesAndImport(QWidget* widget) {
  QStringList fileList =
    QFileDialog::getOpenFileNames(widget,
                                  "Select one or more files to import",
                                  "/home",
                                  "LAS files (*.las)");

  LasFileParser                    lasFileParser;
  QVector<ImportTreeLasFileModel*> importTreeLasFileModels;

  // collect list of parsed las files
  for (QString fileName : fileList) {
    QSharedPointer<LasFile> lf = lasFileParser.parse(fileName);

    importTreeLasFileModels.append(new ImportTreeLasFileModel(lf));
  }

  return importTreeLasFileModels;
}
}
}
