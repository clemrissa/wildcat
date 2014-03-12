#include "ImportWidget.hpp"

#include <Uni/Logging/Logging>

#include <QAbstractItemModel>
#include <QDialogButtonBox>
#include <QFileDialog>
#include <QHeaderView>
#include <QList>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QTreeView>
#include <QVBoxLayout>

#include "ImportController.hpp"
#include "ImportTreeModel.hpp"

#include "Las/ImportTreeWrapperLasFile.hpp"

#include <Uni/Logging/logging>

namespace Geo {
namespace Import {
class ImportWidget::Private {
public:
  QPushButton*    openFileButton;
  QPlainTextEdit* textEdit;

  QTreeView* treeView;

  QAbstractItemModel* importTreeModel;
};

ImportWidget::
ImportWidget(QAbstractItemModel* importModel):
  im(new Private) {
  setWindowTitle("Import Data");

  im->openFileButton = new QPushButton("Import Files");

  //

  im->textEdit = new QPlainTextEdit();

  im->treeView = new QTreeView();

  im->importTreeModel = importModel;

  im->treeView->setModel(im->importTreeModel);
  im->treeView->setAlternatingRowColors(true);
  im->treeView->header()->show();

  QVBoxLayout* layout = new QVBoxLayout(this);

  layout->addWidget(im->openFileButton);
  layout->addWidget(im->textEdit);
  layout->addWidget(im->treeView);

  this->setMinimumSize(QSize(500, 400));
}

ImportWidget::
~ImportWidget() {}

// void
// ImportWidget::
// selectFile() {
// QVector<ImportTreeLasFileModel*> lasFileModels =
// ImportController::instance()->selectFilesAndImport(this);

// for (ImportTreeLasFileModel* model : lasFileModels)
// im->textEdit->appendPlainText(model->getLasFile()->getText());

// im->importTreeModel->setImportTreeLasFileModels(lasFileModels);
// }
} // namespace Import
} // namespace Geo
