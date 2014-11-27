#include "ImportWidget.hpp"

#include <Uni/Logging/Logging>

#include <QtCore/QAbstractItemModel>
#include <QtCore/QList>
#include <QtCore/QPoint>

#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMenu>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>

#include <Database/Connections/Connection>
#include <Database/Connections/ConnectionManager>
#include <DependencyManager/ApplicationContext>

#include "ImportController.hpp"
#include "ImportTreeItemDelegate.hpp"
#include "ImportTreeModel.hpp"

#include "Las/LasImporter.hpp"
#include "Las/TreeWrapper/LasFileEntry.hpp"
#include "MenuFactory.hpp"

#include <Las/TreeWrapper/WellInformation.hpp>

using Geo::Import::Gui::ImportWidget;

struct ImportWidget::Private
{
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

  connectSignals();

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
  using Geo::Import::Gui::ImportTreeItemDelegate;

  p->connectionsComboBox = new QComboBox();

  p->treeView = new QTreeView();

  p->treeView->setContextMenuPolicy(Qt::CustomContextMenu);

  p->treeView->setAlternatingRowColors(true);
  p->treeView->header()->show();
  p->treeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);

  p->treeView->setItemDelegate(new ImportTreeItemDelegate());

  p->dialogButton = new QDialogButtonBox(QDialogButtonBox::Ok);

  auto okButton = p->dialogButton->button(QDialogButtonBox::Ok);
  okButton->setText(tr("Import"));

  QVBoxLayout* layout = new QVBoxLayout(this);

  layout->addWidget(p->connectionsComboBox);
  layout->addWidget(p->treeView);
  layout->addWidget(p->dialogButton);
}


void
ImportWidget::
connectSignals()
{
  connect(p->dialogButton, SIGNAL(accepted()),
          this, SLOT(onImportClicked()));

  connect(p->connectionsComboBox, SIGNAL(activated(int)),
          this, SLOT(onConnectionSelected(int)));

  connect(p->connectionsComboBox, SIGNAL(activated(int)),
          p->treeView, SLOT(expandAll()));

  connect(p->treeView, SIGNAL(customContextMenuRequested(const QPoint &)),
          this, SLOT(onTableViewMenuRequested(const QPoint &)));
}


void
ImportWidget::
setModel(ImportTreeModel* importModel)
{
  p->treeView->setModel(importModel);

  using DependencyManager::ApplicationContext;
  using Geo::Database::Connections::ConnectionManager;

  auto connectionManager =
    ApplicationContext::create<ConnectionManager>(
      "Database.ConnectionManager");

  if (connectionManager->size()) {
    importModel->setConnection(connectionManager->at(0));
    p->treeView->expandAll();
  }
}


void
ImportWidget::
setupDataBinding()
{
  using DependencyManager::ApplicationContext;
  using Geo::Database::Connections::Connection;
  using Geo::Database::Connections::ConnectionManager;

  auto connectionManager =
    ApplicationContext::create<ConnectionManager>(
      "Database.ConnectionManager");

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

  auto importTreeModel =
    static_cast<ImportTreeModel*>(p->treeView->model());
  auto lasFileEntries = importTreeModel->getLasFileEntries();

  QVector<LasFile::Shared> lasFiles;

  for (auto lasFileEntry : lasFileEntries)
    lasFiles.append(lasFileEntry->lasFile());

  int databaseIndex = p->connectionsComboBox->currentIndex();

  LasImporter(databaseIndex).import(lasFiles);

  // close import window
  static_cast<QWidget*>(parent())->close();
}


void
ImportWidget::
onConnectionSelected(int index)
{
  using DependencyManager::ApplicationContext;
  using Geo::Database::Connections::ConnectionManager;

  auto connectionManager =
    ApplicationContext::create<ConnectionManager>(
      "Database.ConnectionManager");

  auto model = static_cast<ImportTreeModel*>(p->treeView->model());

  if (model)
    model->setConnection(connectionManager->at(index));
}


// TODO: remove data processing from GUI
void
ImportWidget::
onTableViewMenuRequested(const QPoint& pos)
{
  QModelIndex index = p->treeView->indexAt(pos);

  if (!index.isValid())
    return;

  using Geo::Import::TreeWrapper::TreeEntry;
  using Geo::Import::TreeWrapper::WellInfoBase;
  using MenuFactory = TreeWrapperMenuFactory;

  TreeEntry* treeEntry =
    static_cast<TreeEntry*>(index.internalPointer());

  WellInfoBase* wellInfo =
    dynamic_cast<WellInfoBase*>(treeEntry);

  if (wellInfo) {
    QSharedPointer<QMenu> menu(MenuFactory::getWellInformationBaseMenu(
                                 wellInfo,
                                 index.column()));

    if (menu.isNull())
      return;

    menu->exec(p->treeView->mapToGlobal(pos));
  }
}
