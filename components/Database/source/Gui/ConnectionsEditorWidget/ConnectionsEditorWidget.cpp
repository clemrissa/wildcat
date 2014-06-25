#include "ConnectionsEditorWidget.hpp"

#include <QHBoxLayout>
#include <QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTreeView>

#include <Gui/ConnectionsEditorWidget/ConnectionEntryItemDelegate.hpp>
#include <Gui/ConnectionsEditorWidget/SQLiteConnectionPropertiesWidget.hpp>

#include <Models/ConnectionsEditorWidgetModel/ConnectionEntry.hpp>
#include <Models/ConnectionsEditorWidgetModel/ConnectionsEditorWidgetModel.hpp>

#include <Uni/Logging/Logging>

using Geo::Database::Gui::ConnectionsEditorWidget;

using Geo::Database::Models::ConnectionsEditorWidgetModel::
      ConnectionsEditorWidgetModel;

struct ConnectionsEditorWidget::Private
{
  QTreeView*      treeView;
  QStackedWidget* stackedWidget;
};

ConnectionsEditorWidget::
ConnectionsEditorWidget(ConnectionsEditorWidgetModel* treeModel):
  p(new ConnectionsEditorWidget::Private())
{
  setupUi(treeModel);
  connectSignals(treeModel);
}

ConnectionsEditorWidget::
~ConnectionsEditorWidget()
{
  delete p;
}

void
ConnectionsEditorWidget::
setupUi(ConnectionsEditorWidgetModel* treeModel)
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
ConnectionsEditorWidget::
connectSignals(ConnectionsEditorWidgetModel* treeModel)
{
  connect(p->treeView, SIGNAL(clicked(const QModelIndex &)),
          treeModel,   SLOT(onClicked(const QModelIndex &)));

  connect(p->treeView, SIGNAL(clicked(const QModelIndex &)),
          this,        SLOT(onConnectionClicked(const QModelIndex &)));
}

void
ConnectionsEditorWidget::
onConnectionClicked(const QModelIndex& index)
{
  using Geo::Database::Models::ConnectionsEditorWidgetModel::ConnectionEntry;

  if (!index.parent().isValid()) {
    bool invalidRow = (index.row() == p->treeView->model()->rowCount() - 1);

    ConnectionEntry* c = invalidRow ? nullptr : static_cast<ConnectionEntry*>(
      index.internalPointer());

    Connections::DatabaseType type =
      c ? c->connection()->databaseType() : Connections::UnknownDB;

    p->stackedWidget->setCurrentIndex((int)type);

    if (c && type != Connections::UnknownDB) {
      QWidget* w =  p->stackedWidget->widget(type);

      ConnectionPropertiesWidget* cpw =
        static_cast<ConnectionPropertiesWidget*>(w);

      cpw->setConnection(c->connection());
    }
  }
}
