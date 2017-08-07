#include "ConnectionsEditorWidget.hpp"

#include <QHBoxLayout>
#include <QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableView>

#include "ConnectionEntryItemDelegate.hpp"

#include "SQLiteConnectionPropertiesWidget.hpp"

#include "ConnectionEntry.hpp"
#include "ConnectionsEditorWidgetModel.hpp"

using Geo::Database::Gui::ConnectionsEditorWidget::ConnectionsEditorWidget;

using Geo::Database::Gui::ConnectionsEditorWidgetModel;

struct ConnectionsEditorWidget::Private
{
  QTableView*     connectionsTable = nullptr;
  QStackedWidget* stackedWidget    = nullptr;
};

ConnectionsEditorWidget::
ConnectionsEditorWidget(ConnectionsEditorWidgetModel* treeModel)
  : p(std::make_unique<Private>())
{
  setupUi(treeModel);
  connectSignals(treeModel);
}


ConnectionsEditorWidget::
~ConnectionsEditorWidget()
{}

void
ConnectionsEditorWidget::
setupUi(ConnectionsEditorWidgetModel* treeModel)
{
  setWindowTitle(tr("Connections Settings"));
  setMinimumSize(800, 400);

  //-----------

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

  //---

  p->stackedWidget = new QStackedWidget();

  QLabel* label = new QLabel("<h5>Create or select database</h5>");

  label->setAlignment(Qt::AlignCenter);

  p->stackedWidget->insertWidget((int)DatabaseType::UnknownDB,
                                 label);

  p->stackedWidget->insertWidget((int)DatabaseType::SQLite,
                                 new SQLiteConnectionPropertiesWidget);

  p->stackedWidget->insertWidget((int)DatabaseType::MongoDB,
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
  using Geo::Database::Gui::ConnectionEntry;

  if (!index.parent().isValid())
  {
    bool invalidRow =
      (index.row() == p->connectionsTable->model()->rowCount() - 1);

    ConnectionEntry* c = invalidRow ? nullptr : static_cast<ConnectionEntry*>(
      index.internalPointer());

    DatabaseType type =
      c ? c->connection()->databaseType() : DatabaseType::UnknownDB;

    p->stackedWidget->setCurrentIndex(static_cast<int>(type));

    if (c && type != DatabaseType::UnknownDB)
    {
      QWidget* w = p->stackedWidget->widget(static_cast<int>(type));

      Mixin::ConnectionAcceptor* cpw =
        dynamic_cast<Mixin::ConnectionAcceptor*>(w);

      cpw->setConnection(c->connection());
    }
  }
}
