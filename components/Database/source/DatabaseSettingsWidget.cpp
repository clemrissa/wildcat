#include "DatabaseSettingsWidget.hpp"

#include <QHBoxLayout>
#include <QStackedWidget>
#include <QTreeView>
#include <QHeaderView>

#include "DatabaseSettingsTreeModel.hpp"
#include "DatabaseSettingsItemDelegate.hpp"

namespace Geo {
namespace Database {
struct DatabaseSettingsWidget::Private {
  QTreeView*      treeView;
  QStackedWidget* stackedWidget;
};

DatabaseSettingsWidget::
DatabaseSettingsWidget(DatabaseSettingsTreeModel* treeModel)
  : p(new DatabaseSettingsWidget::Private()) 
{
  setWindowTitle(tr("Database Settings"));
  setMinimumSize(600, 400);

  p->treeView = new QTreeView();

  p->treeView->setMaximumWidth(300);
  p->treeView->setModel(treeModel);
  p->treeView->header()->setStretchLastSection(false);
  p->treeView->header()->setSectionResizeMode(0, QHeaderView::Stretch);
  p->treeView->header()->setSectionResizeMode(1, QHeaderView::Fixed);
  p->treeView->header()->resizeSection(1, 20);
  p->treeView->setItemDelegate(new DatabaseSettingsItemDelegate());

  p->stackedWidget = new QStackedWidget();

  QHBoxLayout* l = new QHBoxLayout();

  l->addWidget(p->treeView);
  l->addWidget(p->stackedWidget);

  setLayout(l);


  connect(p->treeView,
          SIGNAL(clicked(const QModelIndex&)),
          treeModel,
          SLOT(onClicked(const QModelIndex&)));
}

DatabaseSettingsWidget::
~DatabaseSettingsWidget() {
  delete p;
}
}
}
