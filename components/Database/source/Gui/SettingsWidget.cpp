#include "SettingsWidget.hpp"

#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QStackedWidget>
#include <QTreeView>

#include "SettingsItemDelegate.hpp"
#include "SettingsTreeConnection.hpp"
#include "SettingsTreeModel.hpp"

#include "SQLiteConnectionPropertiesWidget.hpp"

#include <Uni/Logging/Logging>

using Geo::Database::Gui::SettingsWidget;
using Geo::Database::SettingsTreeModel;

struct SettingsWidget::Private {
  QTreeView*      treeView;
  QStackedWidget* stackedWidget;
};

SettingsWidget::
SettingsWidget(SettingsTreeModel* treeModel):
  p(new SettingsWidget::Private())
{
  setupUi(treeModel);
  connectSignals(treeModel);
}


SettingsWidget::
~SettingsWidget()
{
  delete p;
}


void
SettingsWidget::
setupUi(SettingsTreeModel* treeModel)
{
  setWindowTitle(tr("Database Settings"));
  setMinimumSize(700, 400);

  p->treeView = new QTreeView();

  p->treeView->setMaximumWidth(400);

  p->treeView->setModel(treeModel);
  p->treeView->header()->setStretchLastSection(false);
  p->treeView->header()->setSectionResizeMode(0, QHeaderView::Stretch);
  p->treeView->header()->setSectionResizeMode(1, QHeaderView::Fixed);
  p->treeView->header()->resizeSection(1, 20);
  p->treeView->setItemDelegate(new SettingsItemDelegate());

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
}


void
SettingsWidget::
connectSignals(SettingsTreeModel* treeModel)
{
  connect(p->treeView, SIGNAL(clicked(const QModelIndex &)),
          treeModel,   SLOT(onClicked(const QModelIndex &)));

  connect(p->treeView, SIGNAL(clicked(const QModelIndex &)),
          this,        SLOT(onTreeClicked(const QModelIndex &)));
}


void
SettingsWidget::
onTreeClicked(const QModelIndex& index)
{
  if (!index.parent().isValid()) {
    bool invalidRow = (index.row() == p->treeView->model()->rowCount() - 1);

    SettingsTreeConnection* c =
      invalidRow ? nullptr : static_cast<SettingsTreeConnection*>(index.internalPointer());

    DatabaseType type = c ? c->connection()->databaseType() : UnknownDB;

    p->stackedWidget->setCurrentIndex((int)type);

    if (c && type != UnknownDB) {
      QWidget* w =  p->stackedWidget->widget(type);

      ConnectionPropertiesWidget* cpw =
        static_cast<ConnectionPropertiesWidget*>(w);

      cpw->setConnection(c->connection());
    }
  }
}
