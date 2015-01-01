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
  QPushButton* loadXmlButton;

  QPushButton* saveXmlButton;

  // curve types tree
  QTreeView* treeView;

  CurveTypeModel* curveTypeModel;
};

CurveTypeWidget::
CurveTypeWidget():
  p(new Private)
{
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
  setWindowTitle("Curve Types");

  p->loadXmlButton = new QPushButton(tr("Load Slb Xml"));

  p->loadXmlButton->setToolTip(tr("Loads Schlumberger Xml file"));

  p->saveXmlButton = new QPushButton(tr("Save Geo Xml"));

  p->saveXmlButton->setToolTip(tr("Saves curve types to Geo Xml file"));

  // --------------------

  p->curveTypeModel = new CurveTypeModel();

  p->treeView = new QTreeView();

  p->treeView->setModel(p->curveTypeModel);

  p->treeView->setItemDelegate(new CurveTypeEntryDelegate());

  p->treeView->setContextMenuPolicy(Qt::CustomContextMenu);

  p->treeView->setAlternatingRowColors(true);

  p->treeView->setSelectionBehavior(QAbstractItemView::SelectRows);
  p->treeView->setSelectionMode(QAbstractItemView::NoSelection);

  auto header = p->treeView->header();
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

  ll->addWidget(p->loadXmlButton);
  ll->addWidget(p->saveXmlButton);
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

  connect(p->saveXmlButton, SIGNAL(released()),
          this, SLOT(onSaveXmlClicked()));

  // for deleting rows
  connect(p->treeView, SIGNAL(clicked(const QModelIndex &)),
          p->curveTypeModel,   SLOT(onClicked(const QModelIndex &)));

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
                                 tr("Curve Type files (*.xml)"));

  if (fileName.isEmpty())
    return;

  using Geo::TypeSystem::Models::CurveTypes::CurveTypeModel;

  auto curveTypeModel = static_cast<CurveTypeModel*>(p->treeView->model());

  if (curveTypeModel)
    curveTypeModel->loadXml(fileName);
}


void
CurveTypeWidget::
onSaveXmlClicked()
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
    static_cast<CurveTypeModel*>(p->treeView->model());

  if (curveTypeModel)
    curveTypeModel->saveXml(fileName);
}


void
CurveTypeWidget::
setConnection(Database::Connections::Connection::Shared connection)
{
  p->curveTypeModel->setConnection(connection);
}
