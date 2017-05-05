#include "CurveTypeWidget.hpp"

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

#include <Gui/CurveTypes/CurveTypeEntryDelegate.hpp>

#include <DependencyManager/ApplicationContext>
#include <Models/ConnectionListModel>

#include <Models/CurveTypes/CurveTypeModel.hpp>
#include <Models/CurveTypes/TreeEntry.hpp>

using AC = DependencyManager::ApplicationContext;

using Geo::TypeSystem::Gui::CurveTypeEntryDelegate;
using Geo::TypeSystem::Gui::CurveTypeWidget;
using Geo::TypeSystem::Models::CurveTypes::CurveTypeModel;
using Geo::TypeSystem::Models::CurveTypes::TreeEntry;

struct CurveTypeWidget::Private
{
  QPushButton* loadSlbXmlButton;

  QPushButton* saveGeoXmlButton;

  QPushButton* loadGeoXmlButton;

  // curve types tree
  QTreeView* treeView;

  CurveTypeModel* curveTypeModel;
};

CurveTypeWidget::
CurveTypeWidget():
  _p(new Private)
{
  setupUi();

  connectSignals();

  emit notifyMainWindow(tr("Configure available Curve Types"));
}


CurveTypeWidget::
~CurveTypeWidget()
{
  if (_p->curveTypeModel)
    delete _p->curveTypeModel;

  delete _p;
}


void
CurveTypeWidget::
setupUi()
{
  setWindowTitle("Curve Types");

  _p->loadSlbXmlButton = new QPushButton(tr("Load Slb Xml"));

  _p->loadSlbXmlButton->setToolTip(tr("Loads Schlumberger Xml file"));

  _p->saveGeoXmlButton = new QPushButton(tr("Save Geo Xml"));

  _p->saveGeoXmlButton->setToolTip(tr("Saves curve types to Geo Xml file"));

  _p->loadGeoXmlButton = new QPushButton(tr("Load Geo Xml"));

  _p->loadGeoXmlButton->setToolTip(tr("Load curve types from Geo Xml file"));

  // --------------------

  _p->curveTypeModel = new CurveTypeModel();

  _p->treeView = new QTreeView();

  _p->treeView->setModel(_p->curveTypeModel);

  _p->treeView->setItemDelegate(new CurveTypeEntryDelegate());

  _p->treeView->setContextMenuPolicy(Qt::CustomContextMenu);

  _p->treeView->setAlternatingRowColors(true);

  _p->treeView->setSelectionBehavior(QAbstractItemView::SelectRows);
  _p->treeView->setSelectionMode(QAbstractItemView::NoSelection);

  auto header = _p->treeView->header();
  header->setSectionResizeMode(QHeaderView::Stretch);

  header->setSectionResizeMode(TreeEntry::FamilyOrCurveName,
                               QHeaderView::ResizeToContents);

  header->setSectionResizeMode(TreeEntry::Synonyms,
                               QHeaderView::ResizeToContents);

  header->setSectionResizeMode(TreeEntry::Units,
                               QHeaderView::ResizeToContents);

  header->setSectionResizeMode(TreeEntry::Continuity,
                               QHeaderView::ResizeToContents);

  header->setSectionResizeMode(TreeEntry::Scale,
                               QHeaderView::ResizeToContents);

  header->setStretchLastSection(false);

  header->setSectionResizeMode(TreeEntry::CloseAction,
                               QHeaderView::Fixed);

  header->resizeSection(TreeEntry::CloseAction, 20);

  QVBoxLayout* layout = new QVBoxLayout(this);

  layout->setContentsMargins(0, 0, 0, 0);

  auto ll = new QHBoxLayout();

  ll->addWidget(_p->loadSlbXmlButton);
  ll->addWidget(_p->saveGeoXmlButton);
  ll->addWidget(_p->loadGeoXmlButton);
  ll->addStretch();
  layout->addLayout(ll);

  layout->addWidget(_p->treeView);
}


void
CurveTypeWidget::
connectSignals()
{
  connect(_p->loadSlbXmlButton, SIGNAL(released()),
          this, SLOT(onLoadSlbXmlClicked()));

  connect(_p->saveGeoXmlButton, SIGNAL(released()),
          this, SLOT(onSaveGeoXmlClicked()));

  connect(_p->loadGeoXmlButton, SIGNAL(released()),
          this, SLOT(onLoadGeoXmlClicked()));

  // for deleting rows
  connect(_p->treeView, SIGNAL(clicked(const QModelIndex &)),
          _p->curveTypeModel,   SLOT(onClicked(const QModelIndex &)));

  // -------- main window notification
  using Geo::Core::MainWindow;
  auto mainWindow = AC::create<MainWindow>("Core.MainWindow");

  connect(this, SIGNAL(notifyMainWindow(QString)),
          mainWindow, SLOT(setStatus(QString)));
}


// TODO: remove data processing from GUI
void
CurveTypeWidget::
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
CurveTypeWidget::
onLoadSlbXmlClicked()
{
  QString fileName =
    QFileDialog::getOpenFileName(this,
                                 tr("Select a Schlumberger Xml file"),
                                 QString(),
                                 tr("Curve Type files (*.xml)"));

  if (fileName.isEmpty())
    return;

  using Geo::TypeSystem::Models::CurveTypes::CurveTypeModel;

  auto curveTypeModel = static_cast<CurveTypeModel*>(_p->treeView->model());

  if (curveTypeModel)
    curveTypeModel->loadXml(fileName);
}


void
CurveTypeWidget::
onLoadGeoXmlClicked()
{
  QString fileName =
    QFileDialog::getOpenFileName(this,
                                 tr("Select a Geo Curve Xml file"),
                                 QString(),
                                 tr("Curve Type files (*.xml)"));

  if (fileName.isEmpty())
    return;

  using Geo::TypeSystem::Models::CurveTypes::CurveTypeModel;

  auto curveTypeModel = static_cast<CurveTypeModel*>(_p->treeView->model());

  if (curveTypeModel)
    curveTypeModel->loadXml(fileName);
}


void
CurveTypeWidget::
onSaveGeoXmlClicked()
{
  QString fileName =
    QFileDialog::getSaveFileName(this,
                                 tr("Save Geo curve type Xml file"),
                                 QString(),
                                 tr("Database files (*.xml )"));

  if (fileName.isEmpty())
    return;

  using Geo::TypeSystem::Models::CurveTypes::CurveTypeModel;

  auto curveTypeModel =
    static_cast<CurveTypeModel*>(_p->treeView->model());

  if (curveTypeModel)
    curveTypeModel->saveXml(fileName);
}


void
CurveTypeWidget::
setConnection(Database::Connections::Connection::Shared connection)
{
  _p->curveTypeModel->setConnection(connection);
}
