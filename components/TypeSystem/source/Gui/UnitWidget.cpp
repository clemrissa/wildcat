#include "UnitWidget.hpp"

#include <Uni/Logging/Logging>

#include <QtCore/QAbstractItemModel>
#include <QtCore/QList>
#include <QtCore/QPoint>

#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMenu>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>

#include <Core/MainWindow>

#include <DependencyManager/ApplicationContext>
#include <Models/ConnectionListModel>

#include <Models/Units/UnitModel.hpp>

using AC = DependencyManager::ApplicationContext;

using Geo::TypeSystem::Gui::UnitWidget;
using Geo::TypeSystem::Models::Units::UnitModel;

struct UnitWidget::Private
{
  QPushButton* loadXmlButton;

  // curve types tree
  QTreeView* treeView;

  UnitModel* unitsModel;
};

UnitWidget::
UnitWidget():
  _p(new Private)
{
  setupUi();

  connectSignals();

  emit notifyMainWindow(tr("Configure available Units"));
}


UnitWidget::
~UnitWidget()
{
  if (_p->unitsModel)
    delete _p->unitsModel;

  delete _p;
}


void
UnitWidget::
setupUi()
{
  _p->loadXmlButton = new QPushButton(tr("Load Slb Xml"));

  _p->loadXmlButton->setToolTip(tr("Loads Schlumberger Xml file"));

  // --------------------

  _p->unitsModel = new UnitModel();

  _p->treeView = new QTreeView();

  _p->treeView->setModel(_p->unitsModel);

  _p->treeView->setContextMenuPolicy(Qt::CustomContextMenu);

  _p->treeView->setAlternatingRowColors(true);
  _p->treeView->header()->show();
  _p->treeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);

  // _p->treeView->setItemDelegate(new ImportTreeItemDelegate());

  // -- horizontal line

  QFrame* f = new QFrame();

  f->setFrameStyle(QFrame::HLine | QFrame::Sunken);
  f->setLineWidth(3);

  QVBoxLayout* layout = new QVBoxLayout(this);

  layout->addWidget(f);

  auto ll = new QHBoxLayout();

  ll->addWidget(_p->loadXmlButton);
  ll->addStretch();
  layout->addLayout(ll);

  layout->addWidget(_p->treeView);
}


void
UnitWidget::
connectSignals()
{
  connect(_p->loadXmlButton, SIGNAL(released()),
          this, SLOT(onLoadXmlClicked()));

  // -------- main window notification
  using Geo::Core::MainWindow;
  auto mainWindow = AC::create<MainWindow>("Core.MainWindow");

  connect(this, SIGNAL(notifyMainWindow(QString)),
          mainWindow, SLOT(setStatus(QString)));
}


// TODO: remove data processing from GUI
void
UnitWidget::
onTableViewMenuRequested(const QPoint& pos)
{
  Q_UNUSED(pos);

  // QModelIndex index = _p->treeView->indexAt(pos);

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

  // menu->exec(_p->treeView->mapToGlobal(pos));
  // }
}


void
UnitWidget::
setConnection(Database::Connections::Connection::Shared connection)
{
  _p->unitsModel->setConnection(connection);
}
