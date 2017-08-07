#include "ExplorerWidget.hpp"

#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>

#include <QtCore/QDebug>

#include <ComponentManager/Creator>

#include "ExplorerTreeModel.hpp"

namespace Geo
{
namespace Database
{
namespace Gui
{

struct ExplorerWidget::Private
{
  QTreeView* treeView = nullptr;

  std::unique_ptr<ExplorerTreeModel> model;
};

ExplorerWidget::
ExplorerWidget()
  : p(std::make_unique<Private>())
{
  setWindowTitle("Explorer");
  setMinimumSize(200, 200);

  setupUi();

  setupModels();
}


ExplorerWidget::
~ExplorerWidget()
{}

void
ExplorerWidget::
setupUi()
{
  p->treeView = new QTreeView();

  p->treeView->setContextMenuPolicy(Qt::CustomContextMenu);

  p->treeView->setAlternatingRowColors(true);
  p->treeView->header()->show();
  p->treeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);

  //using Geo::Import::Gui::ImportTreeItemDelegate;
  //p->treeView->setItemDelegate(new ImportTreeItemDelegate());

  QVBoxLayout* layout = new QVBoxLayout(this);

  layout->addWidget(p->treeView);
}


void
ExplorerWidget::
setupModels()
{
  p->model.reset(new ExplorerTreeModel());

  p->treeView->setModel(p->model.get());
}


void
ExplorerWidget::
connectSignals()
{
  //
}


//
}
}
}
