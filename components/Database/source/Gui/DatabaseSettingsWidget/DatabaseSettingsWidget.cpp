#include "DatabaseSettingsWidget.hpp"

#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QDialogButtonBox>

#include <Connections/ConnectionManager.hpp>
#include <DependencyManager/ApplicationContext>

#include <Uni/Logging/Logging>

#include <Models/DatabaseSettingsWidgetModel/ConnectionEntry.hpp>
#include <Models/DatabaseSettingsWidgetModel/DatabaseSettingsWidgetModel.hpp>

#include <Gui/DatabaseSettingsWidget/DatabasePropertiesWidget.hpp>

using Geo::Database::Gui::DatabaseSettingsWidget::DatabaseSettingsWidget;

using Geo::Database::Gui::DatabaseSettingsWidget::DatabasePropertiesWidget;
using Geo::Database::Models::DatabaseSettingsWidgetModel::DatabaseSettingsWidgetModel;

struct DatabaseSettingsWidget::Private
{
  //QComboBox* connectionsComboBox;
  QTableView* tableView;

  DatabasePropertiesWidget* traitsWidget;

  QDialogButtonBox* dialogButton;
};

DatabaseSettingsWidget::
DatabaseSettingsWidget(DatabaseSettingsWidgetModel* tableModel):
  p(new DatabaseSettingsWidget::Private())
{
  setupUi(tableModel);
  connectSignals();
}


DatabaseSettingsWidget::
~DatabaseSettingsWidget()
{
  delete p;
}


void
DatabaseSettingsWidget::
setupUi(DatabaseSettingsWidgetModel* tableModel)
{
  setWindowTitle(tr("Database Settings"));
  setMinimumSize(800, 600);

  p->tableView = new QTableView();

  p->tableView->setModel(tableModel);

  p->tableView->setShowGrid(false);
  p->tableView->setFocusPolicy(Qt::NoFocus);

  QHeaderView* horizontalHeader = p->tableView->horizontalHeader();

  horizontalHeader->setStretchLastSection(true);
  horizontalHeader->setSectionResizeMode(0, QHeaderView::ResizeToContents);
  horizontalHeader->setSectionResizeMode(1, QHeaderView::Stretch);

  QHeaderView* verticalHeader = p->tableView->verticalHeader();
  verticalHeader->hide();
  verticalHeader->setSectionResizeMode(QHeaderView::Fixed);
  verticalHeader->setDefaultSectionSize(22);

  // p->tableView->setMaximumWidth(400);
  p->tableView->setMaximumHeight(200);
  p->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

  p->traitsWidget = new DatabasePropertiesWidget();

  //
  p->dialogButton = new QDialogButtonBox(QDialogButtonBox::Ok);

  //auto okButton = p->dialogButton->button(QDialogButtonBox::Ok);
  //okButton->setText(tr("Import"));


  // QHBoxLayout* l = new QHBoxLayout();
  auto l = new QVBoxLayout();

  l->addWidget(p->tableView);
  l->addWidget(p->traitsWidget);
  l->addWidget(p->dialogButton);

  setLayout(l);

  // select first connection
}


void
DatabaseSettingsWidget::
connectSignals()
{
  connect(p->dialogButton, SIGNAL(accepted()),
          this, SLOT(onOkClicked()));

  connect(p->tableView, SIGNAL(clicked(const QModelIndex &)),
          this,         SLOT(onConnectionClicked(const QModelIndex &)));

  // "click on first row in connections list
  using Connections::ConnectionManager;
  using DependencyManager::ApplicationContext;

  auto connectionsManager =
    ApplicationContext::create<ConnectionManager>("Database.ConnectionManager");

  if (connectionsManager->size() > 0) {
    auto connections =  connectionsManager->connections();
    p->traitsWidget->setConnection(connections[0]);
    p->tableView->selectRow(0);
  }
}


void
DatabaseSettingsWidget::
onOkClicked()
{
  // close import window
  static_cast<QWidget*>(parent())->close();
}


void
DatabaseSettingsWidget::
onConnectionClicked(const QModelIndex& index)
{
  using Geo::Database::Models::DatabaseSettingsWidgetModel::ConnectionEntry;

  ConnectionEntry* c =
    static_cast<ConnectionEntry*>(index.internalPointer());

  p->traitsWidget->setConnection(c->connection());
}
