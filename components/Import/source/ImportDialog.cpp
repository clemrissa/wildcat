#include "ImportDialog.hpp"

#include <QList>

#include <QDialogButtonBox>
#include <QFileDialog>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QVBoxLayout>

#include "LasFile.hpp"
#include "LasFileParser.hpp"

namespace Geo {
namespace Import {
class ImportDialog::Private {
public:
  QPushButton*    openFileButton;
  QPlainTextEdit* textEdit;

  QDialogButtonBox* buttonBox;
};

ImportDialog::
ImportDialog():
  im(new Private) {
  setWindowTitle("Import Data");
  setModal(true);

  //

  im->openFileButton = new QPushButton("Import File");

  connect(im->openFileButton, SIGNAL(clicked()), this, SLOT(selectFile()));

  //

  im->textEdit = new QPlainTextEdit();

  //

  im->buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok |
                                       QDialogButtonBox::Cancel);

  connect(im->buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
  connect(im->buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

  //

  QVBoxLayout* layout = new QVBoxLayout(this);

  layout->addWidget(im->openFileButton);
  layout->addWidget(im->textEdit);
  layout->addWidget(im->buttonBox);
}

ImportDialog::
~ImportDialog() {}

void
ImportDialog::
selectFile() {
  QString fileName =  QFileDialog::getOpenFileName(this,
                                                   "Select file to import");

  LASFileParser parser;
  LASFile       lasFile;

  if (!fileName.isEmpty())
    lasFile = parser.parse(fileName);

  im->textEdit->appendPlainText(lasFile.getText());
}
}         // namespace Import
}         // namespace Geo
