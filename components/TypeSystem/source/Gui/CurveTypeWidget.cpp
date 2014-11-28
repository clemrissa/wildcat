#include "CurveTypeWidget.hpp"

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

// #include <Database/Connections/Connection>
// #include <Database/Connections/ConnectionManager>

#include <Core/MainWindow>

#include <DependencyManager/ApplicationContext>
#include <Models/ConnectionListModel>

using AC = DependencyManager::ApplicationContext;

using Geo::TypeSystem::Gui::CurveTypeWidget;

struct CurveTypeWidget::Private
{
  // list of DB connections
  QComboBox* connectionsComboBox;

  // curve types tree
  QTreeView* treeView;

  // Press OK to ok
  QDialogButtonBox* dialogButton;
};

CurveTypeWidget::
CurveTypeWidget():
  p(new Private)
{
  setWindowTitle("Curve Types");
  setMinimumSize(QSize(800, 400));

  setupUi();

  connectSignals();

  emit notifyMainWindow(tr("Configure available Curve Types"));
}


CurveTypeWidget::
~CurveTypeWidget()
{
  delete p;
}


void
CurveTypeWidget::
setupUi()
{
  // --------------------

  p->connectionsComboBox = new QComboBox();

  using CLM = Geo::Models::ConnectionListModel;
  auto m = AC::create<CLM>("Models.ConnectionListModel");

  p->connectionsComboBox->setModel(m);

  // --------------------

  p->treeView = new QTreeView();

  p->treeView->setContextMenuPolicy(Qt::CustomContextMenu);

  p->treeView->setAlternatingRowColors(true);
  p->treeView->header()->show();
  p->treeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);

  // p->treeView->setItemDelegate(new ImportTreeItemDelegate());

  p->dialogButton = new QDialogButtonBox(QDialogButtonBox::Ok);

  QVBoxLayout* layout = new QVBoxLayout(this);

  layout->addWidget(p->connectionsComboBox);
  layout->addWidget(p->treeView);
  layout->addWidget(p->dialogButton);
}


void
CurveTypeWidget::
connectSignals()
{
  connect(p->dialogButton, SIGNAL(accepted()),
          this, SLOT(onImportClicked()));

  connect(p->connectionsComboBox, SIGNAL(activated(int)),
          this, SLOT(onConnectionSelected(int)));

  // connect(p->connectionsComboBox, SIGNAL(activated(int)),
  // p->treeView, SLOT(expandAll()));

  // connect(p->treeView, SIGNAL(customContextMenuRequested(const QPoint &)),
  // this, SLOT(onTableViewMenuRequested(const QPoint &)));

  // -------- main window notification
  using       Geo::Core::MainWindow;
  MainWindow* mainWindow = AC::create<MainWindow>("Core.MainWindow");

  connect(this, SIGNAL(notifyMainWindow(QString)),
          mainWindow, SLOT(setStatus(QString)));
}


// void
// CurveTypeWidget::
// setModel(ImportTreeModel* importModel)
// {
// p->treeView->setModel(importModel);

// using DependencyManager::ApplicationContext;
// using Geo::Database::Connections::ConnectionManager;

// auto connectionManager =
// ApplicationContext::create<ConnectionManager>(
// "Database.ConnectionManager");

// if (connectionManager->size()) {
// importModel->setConnection(connectionManager->at(0));
// p->treeView->expandAll();
// }
// }

void
CurveTypeWidget::
onImportClicked()
{
  // close import window
  static_cast<QWidget*>(parent())->close();
}


void
CurveTypeWidget::
onConnectionSelected(int index)
{
  // using CM = Database::Connections::ConnectionManager;

  // auto cm = AC::create<CM>("Database.ConnectionManager");

  // auto model = static_cast<ImportTreeModel*>(p->treeView->model());

  // if (model)
  // model->setConnection(cm->connections()[index]);
}


// TODO: remove data processing from GUI
void
CurveTypeWidget::
onTableViewMenuRequested(const QPoint& pos)
{
  // QModelIndex index = p->treeView->indexAt(pos);

  // if (!index.isValid())
  // return;

  // using Geo::Import::TreeWrapper::TreeEntry;
  // using Geo::Import::TreeWrapper::WellInfoBase;
  // using MenuFactory = TreeWrapperMenuFactory;

  // TreeEntry* treeEntry =
  // static_cast<TreeEntry*>(index.internalPointer());

  // WellInfoBase* wellInfo =
  // dynamic_cast<WellInfoBase*>(treeEntry);

  // if (wellInfo) {
  // QSharedPointer<QMenu> menu(MenuFactory::getWellInformationBaseMenu(
  // wellInfo,
  // index.column()));

  // if (menu.isNull())
  // return;

  // menu->exec(p->treeView->mapToGlobal(pos));
  // }
}
