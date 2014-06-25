#include "DatabaseSettingsWidget.hpp"

#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableView>

#include <Uni/Logging/Logging>

#include <Models/SettingsWidgetModel/ConnectionEntry.hpp>
#include <Models/SettingsWidgetModel/SettingsWidgetModel.hpp>

#include <Gui/DatabaseSettingsWidget/DatabasePropertiesWidget.hpp>

using Geo::Database::Gui::DatabaseSettingsWidget;

using Geo::Database::Gui::DatabasePropertiesWidget;

using Geo::Database::Models::SettingsWidgetModel::
      SettingsWidgetModel;

struct DatabaseSettingsWidget::Private
{
  QTableView* tableView;

  DatabasePropertiesWidget* traitsWidget;
};

DatabaseSettingsWidget::
DatabaseSettingsWidget(SettingsWidgetModel* tableModel):
  p(new DatabaseSettingsWidget::Private())
{
  setupUi(tableModel);
  connectSignals(tableModel);
}

DatabaseSettingsWidget::
~DatabaseSettingsWidget()
{
  delete p;
}

void
DatabaseSettingsWidget::
setupUi(SettingsWidgetModel* tableModel)
{
  setWindowTitle(tr("Database Settings"));
  setMinimumSize(800, 400);

  p->tableView = new QTableView();

  p->tableView->setModel(tableModel);

  p->tableView->horizontalHeader()->setStretchLastSection(true);
  p->tableView->horizontalHeader()->setSectionResizeMode(0,
                                                         QHeaderView::ResizeToContents);
  p->tableView->horizontalHeader()->setSectionResizeMode(1,
                                                         QHeaderView::Stretch);
  p->tableView->setShowGrid(false);

  p->tableView->verticalHeader()->hide();
  QHeaderView* verticalHeader = p->tableView->verticalHeader();
  // verticalHeader->setResizeMode(QHeaderView::Fixed);
  verticalHeader->setDefaultSectionSize(22);

  p->tableView->setMaximumWidth(400);
  p->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

  p->traitsWidget = new DatabasePropertiesWidget();

  QHBoxLayout* l = new QHBoxLayout();

  l->addWidget(p->tableView);
  l->addWidget(p->traitsWidget);

  setLayout(l);
}

void
DatabaseSettingsWidget::
connectSignals(SettingsWidgetModel* tableModel)
{
  connect(p->tableView, SIGNAL(activated(const QModelIndex &)),
          this,         SLOT(onConnectionClicked(const QModelIndex &)));

  // TODO "click on first row"
  p->tableView->selectRow(0);
}

void
DatabaseSettingsWidget::
onConnectionClicked(const QModelIndex& index)
{
  //
  Q_UNUSED(index);
}
