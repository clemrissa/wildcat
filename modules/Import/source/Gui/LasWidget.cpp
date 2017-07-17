#include "LasWidget.hpp"

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

#include <Core/MainWindow>

#include <Models/ConnectionListModel>

#include <ComponentManager/Creator>

#include "ImportController.hpp"
#include "ImportTreeItemDelegate.hpp"
#include "ImportTreeModel.hpp"

#include "Las/LasImporter.hpp"
#include "Las/TreeWrapper/LasFileEntry.hpp"
#include "MenuFactory.hpp"

#include <Las/TreeWrapper/WellInformation.hpp>

using Geo::Import::Gui::LasWidget;

struct LasWidget::Private
{
  Private() :
    treeView(nullptr),
    importTreeModel(nullptr)
  {}

  QTreeView* treeView;

  ImportTreeModel* importTreeModel;
};

LasWidget::
LasWidget() :
  _p(new Private)
{
  setupUi();
  connectSignals();

  emit notifyMainWindow(tr("Select a database and check import data"));
}


LasWidget::
~LasWidget()
{
  if (_p->importTreeModel)
    delete _p->importTreeModel;

  delete _p;
}


void
LasWidget::
setModel(ImportTreeModel* importModel)
{
  _p->treeView->setModel(importModel);
}


void
LasWidget::
setConnection(Database::Connection::Shared connection)
{
  if (_p->importTreeModel)
    _p->importTreeModel->setConnection(connection);
}


void
LasWidget::
setupUi()
{
  _p->treeView = new QTreeView();

  _p->treeView->setContextMenuPolicy(Qt::CustomContextMenu);

  _p->treeView->setAlternatingRowColors(true);
  _p->treeView->header()->show();
  _p->treeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);

  using Geo::Import::Gui::ImportTreeItemDelegate;
  _p->treeView->setItemDelegate(new ImportTreeItemDelegate());

  QVBoxLayout* layout = new QVBoxLayout(this);

  layout->addWidget(_p->treeView);
}


void
LasWidget::
connectSignals()
{
  connect(_p->treeView, SIGNAL(customContextMenuRequested(const QPoint&)),
          this, SLOT(onTableViewMenuRequested(const QPoint&)));

  // -------- main window notification
  using       Geo::Core::MainWindow;
  MainWindow* mainWindow = ComponentManager::create<MainWindow*>("Core.MainWindow");

  connect(this, SIGNAL(notifyMainWindow(QString)),
          mainWindow, SLOT(setStatus(QString)));
}


// void
// LasWidget::
// onImportClicked()
// {
//// take selected database  and push data into there

// auto importTreeModel =
// static_cast<ImportTreeModel*>(p->treeView->model());
// auto lasFileEntries = importTreeModel->getLasFileEntries();

// QVector<LasFile::Shared> lasFiles;

// for (auto lasFileEntry : lasFileEntries)
// lasFiles.append(lasFileEntry->lasFile());

// int databaseIndex =_p->connectionsComboBox->currentIndex();

// LasImporter(databaseIndex).import(lasFiles);

//// close import window
// static_cast<QWidget*>(parent())->close();
// }

// void
// LasWidget::
// onConnectionSelected(int index)
// {
// using CM = Database::ConnectionManager;

// auto cm = AC::create<CM>("Database.ConnectionManager");

// auto model = static_cast<ImportTreeModel*>(p->treeView->model());

// if (model)
// model->setConnection(cm->connections()[index]);
// }

// TODO: remove data processing from GUI
void
LasWidget::
onTableViewMenuRequested(const QPoint& pos)
{
  QModelIndex index = _p->treeView->indexAt(pos);

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

    menu->exec(_p->treeView->mapToGlobal(pos));
  }
}
