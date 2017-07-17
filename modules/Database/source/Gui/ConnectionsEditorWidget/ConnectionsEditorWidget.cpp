#include "ConnectionsEditorWidget.hpp"

#include <QHBoxLayout>
#include <QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableView>

#include <Gui/ConnectionsEditorWidget/ConnectionEntryItemDelegate.hpp>
#include <Gui/ConnectionsEditorWidget/SQLiteConnectionPropertiesWidget.hpp>

#include <Models/ConnectionsEditorWidgetModel/ConnectionEntry.hpp>
#include <Models/ConnectionsEditorWidgetModel/ConnectionsEditorWidgetModel.hpp>

using Geo::Database::Gui::ConnectionsEditorWidget::ConnectionsEditorWidget;

using Geo::Database::Models::ConnectionsEditorWidgetModel;

struct ConnectionsEditorWidget::Private
{
  QTableView*     connectionsTable;
  QStackedWidget* stackedWidget;
};

ConnectionsEditorWidget::
ConnectionsEditorWidget(ConnectionsEditorWidgetModel* treeModel)
  : p(new ConnectionsEditorWidget::Private())
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
  setWindowTitle(tr("Connections Settings"));
  setMinimumSize(800, 400);

  p->connectionsTable = new QTableView();

  p->connectionsTable->setMaximumWidth(400);

  p->connectionsTable->setModel(treeModel);

  p->connectionsTable->setShowGrid(false);
  p->connectionsTable->setFocusPolicy(Qt::NoFocus);

  QHeaderView* horizontalHeader = p->connectionsTable->horizontalHeader();

  horizontalHeader->setStretchLastSection(false);
  horizontalHeader->setSectionResizeMode(0, QHeaderView::ResizeToContents);
  horizontalHeader->setSectionResizeMode(1, QHeaderView::Stretch);
  horizontalHeader->setSectionResizeMode(2, QHeaderView::Fixed);
  horizontalHeader->resizeSection(2, 20);

  QHeaderView* verticalHeader = p->connectionsTable->verticalHeader();
  verticalHeader->hide();
  verticalHeader->setSectionResizeMode(QHeaderView::Fixed);
  verticalHeader->setDefaultSectionSize(22);

  p->connectionsTable->setItemDelegate(new ConnectionEntryItemDelegate());

  p->connectionsTable->setSelectionBehavior(QAbstractItemView::SelectRows);

  p->stackedWidget = new QStackedWidget();

  QLabel* label = new QLabel("<h5>Create or select database</h5>");

  label->setAlignment(Qt::AlignCenter);

  p->stackedWidget->insertWidget((int)Connections::DatabaseType::UnknownDB,
                                 label);

  p->stackedWidget->insertWidget((int)Connections::DatabaseType::SQLite,
                                 new SQLiteConnectionPropertiesWidget);

  QHBoxLayout* l = new QHBoxLayout();

  l->addWidget(p->connectionsTable);
  l->addWidget(p->stackedWidget);

  setLayout(l);
}


void
ConnectionsEditorWidget::
connectSignals(ConnectionsEditorWidgetModel* treeModel)
{
  // for deleting rows
  connect(p->connectionsTable, SIGNAL(clicked(const QModelIndex&)),
          treeModel,   SLOT(onClicked(const QModelIndex&)));

  // for assgning connection to widget
  connect(p->connectionsTable, SIGNAL(clicked(const QModelIndex&)),
          this,        SLOT(onConnectionClicked(const QModelIndex&)));
}


void
ConnectionsEditorWidget::
onConnectionClicked(const QModelIndex& index)
{
  using Geo::Database::Models::ConnectionEntry;

  if (!index.parent().isValid())
  {
    bool invalidRow =
      (index.row() == p->connectionsTable->model()->rowCount() - 1);

    ConnectionEntry* c = invalidRow ? nullptr : static_cast<ConnectionEntry*>(
      index.internalPointer());

    Connections::DatabaseType type =
      c ? c->connection()->databaseType() : Connections::UnknownDB;

    p->stackedWidget->setCurrentIndex((int)type);

    if (c && type != Connections::UnknownDB)
    {
      QWidget* w = p->stackedWidget->widget(type);

      Mixin::ConnectionAcceptor* cpw =
        dynamic_cast<Mixin::ConnectionAcceptor*>(w);

      cpw->setConnection(c->connection());
    }
  }
}
