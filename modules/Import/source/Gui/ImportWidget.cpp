#include "ImportWidget.hpp"

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

#include <Database/Connections/IConnection>
#include <Database/Connections/IConnectionManager>

#include <Core/IMainWindow>

#include <Models/ConnectionListModel>

#include <ComponentManager/Creator>

#include "ImportController.hpp"
#include "ImportTreeItemDelegate.hpp"
#include "ImportTreeModel.hpp"

#include "Las/TreeWrapper/LasFileEntry.hpp"
#include "MenuFactory.hpp"

#include <Las/TreeWrapper/WellInformation.hpp>

using Geo::Import::Gui::ImportWidget;

struct ImportWidget::Private
{
  QComboBox* connectionsComboBox = nullptr;

  QTreeView* treeView = nullptr;

  QDialogButtonBox* dialogButton = nullptr;
};

ImportWidget::
ImportWidget()
  : p(std::make_unique<Private>())
{
  setWindowTitle("Import Data");
  setMinimumSize(QSize(800, 400));

  setupUi();

  connectSignals();

  emit notifyMainWindow(tr("Select a database and check import data"));
}


ImportWidget::
~ImportWidget()
{}


void
ImportWidget::
setupUi()
{
  // --------------------

  p->connectionsComboBox = new QComboBox();

  using CLM = Geo::Models::ConnectionListModel;
  auto m = ComponentManager::create<CLM*>("Models.ConnectionListModel");

  p->connectionsComboBox->setModel(m);

  // --------------------

  p->treeView = new QTreeView();

  p->treeView->setContextMenuPolicy(Qt::CustomContextMenu);

  p->treeView->setAlternatingRowColors(true);
  p->treeView->header()->show();
  p->treeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);

  using Geo::Import::Gui::ImportTreeItemDelegate;
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

  connect(p->treeView, SIGNAL(customContextMenuRequested(const QPoint&)),
          this, SLOT(onTableViewMenuRequested(const QPoint&)));

  // -------- main window notification
  using Geo::Core::IMainWindow;

  IMainWindow* mainWindow = ComponentManager::create<IMainWindow*>("Core.MainWindow");

  connect(this, SIGNAL(notifyMainWindow(QString)),
          mainWindow, SLOT(setStatus(QString)));
}


void
ImportWidget::
setModel(ImportTreeModel* importModel)
{
  p->treeView->setModel(importModel);

  using Geo::Database::IConnectionManager;

  auto connectionManager =
    ComponentManager::create<IConnectionManager*>("Database.ConnectionManager");

  if (connectionManager->size())
  {
    importModel->setConnection((*connectionManager)[0]);
    p->treeView->expandAll();
  }
}


void
ImportWidget::
onImportClicked()
{
  // take selected database  and push data into there

  auto importTreeModel =
    static_cast<ImportTreeModel*>(p->treeView->model());
  auto const & lasFileEntries = importTreeModel->getLasFileEntries();

  QVector<std::shared_ptr<LasFile> > lasFiles;

  for (auto & lasFileEntry : lasFileEntries)
    lasFiles.append(lasFileEntry->lasFile());

  int databaseIndex = p->connectionsComboBox->currentIndex();

  Q_UNUSED(databaseIndex);

  //

  // close import window
  static_cast<QWidget*>(parent())->close();
}


void
ImportWidget::
onConnectionSelected(int index)
{
  using CM = Database::IConnectionManager;

  auto cm = ComponentManager::create<CM*>("Database.ConnectionManager");

  auto model = static_cast<ImportTreeModel*>(p->treeView->model());

  if (model)
    model->setConnection(cm->connections()[index]);
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

  if (wellInfo)
  {
    QSharedPointer<QMenu> menu(MenuFactory::getWellInformationBaseMenu(
                                 wellInfo,
                                 index.column()));

    if (menu.isNull())
      return;

    menu->exec(p->treeView->mapToGlobal(pos));
  }
}
