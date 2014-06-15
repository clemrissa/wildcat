#include "ImportWidget.hpp"

#include <Uni/Logging/Logging>

#include <QAbstractItemModel>
#include <QComboBox>
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

#include "Las/ImportTreeWrapperLasFile.hpp"

namespace Geo {
namespace Import {
// ----------------------------------
struct ImportWidget::Private {
  QComboBox* connectionsComboBox;

  QTreeView* treeView;
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

  QVBoxLayout* layout = new QVBoxLayout(this);

  layout->addWidget(p->connectionsComboBox);
  layout->addWidget(p->treeView);
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
} // namespace Import
} // namespace Geo
