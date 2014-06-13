#include "DatabaseSettingsWidget.hpp"

#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QStackedWidget>
#include <QTreeView>

#include "DatabaseSettingsItemDelegate.hpp"
#include "DatabaseSettingsTreeConnection.hpp"
#include "DatabaseSettingsTreeModel.hpp"

#include "SQLiteConnectionPropertiesWidget.hpp"

#include <Uni/Logging/Logging>

namespace Geo {
namespace Database {
struct DatabaseSettingsWidget::Private {
  QTreeView*      treeView;
  QStackedWidget* stackedWidget;
};

DatabaseSettingsWidget::
DatabaseSettingsWidget(DatabaseSettingsTreeModel* treeModel):
  p(new DatabaseSettingsWidget::Private()) {
  setWindowTitle(tr("Database Settings"));
  setMinimumSize(700, 400);

  p->treeView = new QTreeView();

  p->treeView->setMaximumWidth(300);

  p->treeView->setModel(treeModel);
  p->treeView->header()->setStretchLastSection(false);
  p->treeView->header()->setSectionResizeMode(0, QHeaderView::Stretch);
  p->treeView->header()->setSectionResizeMode(1, QHeaderView::Fixed);
  p->treeView->header()->resizeSection(1, 20);
  p->treeView->setItemDelegate(new DatabaseSettingsItemDelegate());

  p->treeView->setSelectionBehavior(QAbstractItemView::SelectRows);

  p->stackedWidget = new QStackedWidget();

  QLabel* label = new QLabel("<h5>Create or select database</h5>");

  label->setAlignment(Qt::AlignCenter);

  p->stackedWidget->insertWidget((int)DatabaseType::UnknownDB,
                                 label);

  p->stackedWidget->insertWidget((int)DatabaseType::SQLite,
                                 new SQLiteConnectionPropertiesWidget);

  QHBoxLayout* l = new QHBoxLayout();

  l->addWidget(p->treeView);
  l->addWidget(p->stackedWidget);

  setLayout(l);

  connect(p->treeView,
          SIGNAL(clicked(const QModelIndex &)),
          treeModel,
          SLOT(onClicked(const QModelIndex &)));

  connect(p->treeView,
          SIGNAL(clicked(const QModelIndex &)),
          this,
          SLOT(onTreeClicked(const QModelIndex &)));
}

DatabaseSettingsWidget::
~DatabaseSettingsWidget() {
  delete p;
}

void
DatabaseSettingsWidget::
onTreeClicked(const QModelIndex& index) {
  if (!index.parent().isValid()) {
    bool invalidRow = (index.row() == p->treeView->model()->rowCount() - 1);

    DatabaseSettingsTreeConnection* c = invalidRow ? nullptr :
                                        static_cast<DatabaseSettingsTreeConnection*>(
      index.internalPointer());

    DatabaseType type = c ? c->connection()->databaseType() : UnknownDB;

    p->stackedWidget->setCurrentIndex((int)type);

    // if (c)
    // p->stackedWidget->setConnection(c->connection());
  }
}
}
}
