#include "CurveTypeWidget.hpp"

#include <Uni/Logging/Logging>

#include <QtCore/QAbstractItemModel>
#include <QtCore/QList>
#include <QtCore/QPoint>

#include <QtWidgets/QFileDialog>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMenu>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>

// #include <Database/Connections/Connection>
// #include <Database/Connections/ConnectionManager>

#include <Core/MainWindow>

#include <DependencyManager/ApplicationContext>
#include <Models/ConnectionListModel>

#include <Models/CurveTypeModel.hpp>

using AC = DependencyManager::ApplicationContext;

using Geo::TypeSystem::Gui::CurveTypeWidget;
using Geo::TypeSystem::Models::CurveTypeModel;

struct CurveTypeWidget::Private
{
  QPushButton* loadXmlButton;

  // curve types tree
  QTreeView* treeView;

  CurveTypeModel* curveTypeModel;
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
  if (p->curveTypeModel)
    delete p->curveTypeModel;

  delete p;
}


void
CurveTypeWidget::
setupUi()
{
  p->loadXmlButton = new QPushButton(tr("Load Slb Xml"));

  p->loadXmlButton->setToolTip(tr("Loads Schlumberger Xml file"));

  // --------------------

  p->curveTypeModel = new CurveTypeModel();

  p->treeView = new QTreeView();

  p->treeView->setModel(p->curveTypeModel);

  p->treeView->setContextMenuPolicy(Qt::CustomContextMenu);

  p->treeView->setAlternatingRowColors(true);
  p->treeView->header()->show();
  p->treeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);

  // p->treeView->setItemDelegate(new ImportTreeItemDelegate());

  // -- horizontal line

  QFrame* f = new QFrame();

  f->setFrameStyle(QFrame::HLine | QFrame::Sunken);
  f->setLineWidth(3);

  QVBoxLayout* layout = new QVBoxLayout(this);

  layout->addWidget(f);

  auto ll = new QHBoxLayout();

  ll->addWidget(p->loadXmlButton);
  ll->addStretch();
  layout->addLayout(ll);

  layout->addWidget(p->treeView);
}


void
CurveTypeWidget::
connectSignals()
{
  connect(p->loadXmlButton, SIGNAL(released()),
          this, SLOT(onLoadXmlClicked()));

  // -------- main window notification
  using Geo::Core::MainWindow;
  auto mainWindow = AC::create<MainWindow>("Core.MainWindow");

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
  // QSharedPointer<QMenu>
  // menu(MenuFactory::getWellInformationBaseMenu(
  // wellInfo,
  // index.column()));

  // if (menu.isNull())
  // return;

  // menu->exec(p->treeView->mapToGlobal(pos));
  // }
}


void
CurveTypeWidget::
onLoadXmlClicked()
{
  QString fileName =
    QFileDialog::getOpenFileName(this, 
                                 tr("Select a Schlumberger Xml file"),
                                 QString(),
                                 tr("Database files (*.xml)"));

  if (fileName.isEmpty())
    return;


  using Geo::TypeSystem::Models::CurveTypeModel;

  auto curveTypeModel = static_cast<CurveTypeModel*>(p->treeView->model());

  if (curveTypeModel)
      curveTypeModel->loadXml(fileName);


}

void
CurveTypeWidget::
setConnection(Database::Connections::Connection::Shared connection) 
{
  p->curveTypeModel->setConnection(connection);
}
