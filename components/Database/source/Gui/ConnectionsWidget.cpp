#include "ConnectionsWidget.hpp"

#include <QHBoxLayout>
#include <QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTreeView>

#include <Gui/ConnectionEntryItemDelegate.hpp>
#include <Gui/SQLiteConnectionPropertiesWidget.hpp>

#include <Models/ConnectionsWidgetModel/ConnectionEntry.hpp>
#include <Models/ConnectionsWidgetModel/ConnectionsWidgetModel.hpp>

#include <Uni/Logging/Logging>

using Geo::Database::Gui::ConnectionsWidget;

using Geo::Database::Models::ConnectionsWidgetModel::ConnectionsWidgetModel;

struct ConnectionsWidget::Private {
  QTreeView*      treeView;
  QStackedWidget* stackedWidget;
};

ConnectionsWidget::
ConnectionsWidget(ConnectionsWidgetModel* treeModel):
  p(new ConnectionsWidget::Private())
{
  setupUi(treeModel);
  connectSignals(treeModel);
}


ConnectionsWidget::
~ConnectionsWidget()
{
  delete p;
}


void
ConnectionsWidget::
setupUi(ConnectionsWidgetModel* treeModel)
{
  setWindowTitle(tr("Database Settings"));
  setMinimumSize(800, 400);

  p->treeView = new QTreeView();

  p->treeView->setMaximumWidth(400);

  p->treeView->setModel(treeModel);
  p->treeView->header()->setStretchLastSection(false);
  p->treeView->header()->setSectionResizeMode(0, QHeaderView::Stretch);
  p->treeView->header()->setSectionResizeMode(1, QHeaderView::Fixed);
  p->treeView->header()->resizeSection(1, 20);
  p->treeView->setItemDelegate(new ConnectionEntryItemDelegate());

  p->treeView->setSelectionBehavior(QAbstractItemView::SelectRows);

  p->stackedWidget = new QStackedWidget();

  QLabel* label = new QLabel("<h5>Create or select database</h5>");

  label->setAlignment(Qt::AlignCenter);

  p->stackedWidget->insertWidget((int)Connections::DatabaseType::UnknownDB,
                                 label);

  p->stackedWidget->insertWidget((int)Connections::DatabaseType::SQLite,
                                 new SQLiteConnectionPropertiesWidget);

  QHBoxLayout* l = new QHBoxLayout();

  l->addWidget(p->treeView);
  l->addWidget(p->stackedWidget);

  setLayout(l);
}


void
ConnectionsWidget::
connectSignals(ConnectionsWidgetModel* treeModel)
{
  connect(p->treeView, SIGNAL(clicked(const QModelIndex &)),
          treeModel,   SLOT(onClicked(const QModelIndex &)));

  connect(p->treeView, SIGNAL(clicked(const QModelIndex &)),
          this,        SLOT(onConnectionClicked(const QModelIndex &)));
}


void
ConnectionsWidget::
onConnectionClicked(const QModelIndex& index)
{
  using Geo::Database::Models::ConnectionsWidgetModel::ConnectionEntry;

  if (!index.parent().isValid()) {
    bool invalidRow = (index.row() == p->treeView->model()->rowCount() - 1);

    ConnectionEntry* c = invalidRow ? nullptr : static_cast<ConnectionEntry*>(index.internalPointer());

    Connections::DatabaseType type = c ? c->connection()->databaseType() : Connections::UnknownDB;

    p->stackedWidget->setCurrentIndex((int)type);

    if (c && type != Connections::UnknownDB) {
      QWidget* w =  p->stackedWidget->widget(type);

      ConnectionPropertiesWidget* cpw =
        static_cast<ConnectionPropertiesWidget*>(w);

      cpw->setConnection(c->connection());
    }
  }
}
