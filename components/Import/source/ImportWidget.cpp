#include "ImportWidget.hpp"

#include <Uni/Logging/Logging>

#include <QAbstractItemModel>
#include <QComboBox>
#include <QDialogButtonBox>
#include <QDialogButtonBox>
#include <QFileDialog>
#include <QHeaderView>
#include <QList>
#include <QPushButton>
#include <QTreeView>
#include <QVBoxLayout>

#include <Database/Connection>
#include <Database/ConnectionManager>
#include <DependencyManager/ApplicationContext>

#include "ImportController.hpp"
#include "ImportTreeModel.hpp"

#include "Las/TreeWrapper/LasFileEntry.hpp"

namespace Geo {
namespace Import {
//
//
struct ImportWidget::Private {
  QComboBox* connectionsComboBox;

  QTreeView* treeView;

  QDialogButtonBox* dialogButton;
};

ImportWidget::
ImportWidget():
  p(new Private)
{
  setWindowTitle("Import Data");
  setMinimumSize(QSize(800, 400));

  setupUi();

  setupDataBinding();
}


ImportWidget::
~ImportWidget()
{
  delete p;
}


void
ImportWidget::
setupUi()
{
  p->connectionsComboBox = new QComboBox();

  p->treeView = new QTreeView();

  p->treeView->setAlternatingRowColors(true);
  p->treeView->header()->show();
  p->treeView->header()->setSectionResizeMode(QHeaderView::Stretch);

  p->dialogButton = new QDialogButtonBox(QDialogButtonBox::Ok);

  auto okButton =  p->dialogButton->button(QDialogButtonBox::Ok);
  okButton->setText(tr("Import"));

  QVBoxLayout* layout = new QVBoxLayout(this);

  layout->addWidget(p->connectionsComboBox);
  layout->addWidget(p->treeView);
  layout->addWidget(p->dialogButton);

  connect(p->dialogButton, SIGNAL(accepted()),
          this, SLOT(onImportClicked()));
}


void
ImportWidget::
setModel(QAbstractItemModel* importModel)
{
  p->treeView->setModel(importModel);
}


void
ImportWidget::
setupDataBinding()
{
  using DependencyManager::ApplicationContext;
  using Geo::Database::Connection;
  using Geo::Database::ConnectionManager;

  auto connectionManager =
    ApplicationContext::create<ConnectionManager>("Database.ConnectionManager");

  for (int i = 0; i < connectionManager->size(); ++i) {
    Connection::Shared c = connectionManager->at(i);
    p->connectionsComboBox->addItem(c->textDescription());
  }
}


void
ImportWidget::
onImportClicked()
{
  // take selected database  and push data into there

  // close import window
  static_cast<QWidget*>(parent())->close();
}


//
} // namespace Import
} // namespace Geo
