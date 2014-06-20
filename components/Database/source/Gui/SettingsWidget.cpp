#include "SettingsWidget.hpp"

#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableView>

#include <Uni/Logging/Logging>

#include <Models/SettingsWidgetModel/ConnectionEntry.hpp>
#include <Models/SettingsWidgetModel/SettingsWidgetModel.hpp>

using Geo::Database::Gui::SettingsWidget;

using Geo::Database::Models::SettingsWidgetModel::SettingsWidgetModel;

struct SettingsWidget::Private {
  QTableView*     tableView;
  QStackedWidget* stackedWidget;
};

SettingsWidget::
SettingsWidget(SettingsWidgetModel* tableModel):
  p(new SettingsWidget::Private())
{
  setupUi(tableModel);
  connectSignals(tableModel);
}


SettingsWidget::
~SettingsWidget()
{
  delete p;
}


void
SettingsWidget::
setupUi(SettingsWidgetModel* tableModel)
{
  setWindowTitle(tr("Database Settings"));
  setMinimumSize(800, 400);

  p->tableView = new QTableView();

  p->tableView->setModel(tableModel);

  p->tableView->horizontalHeader()->setStretchLastSection(true);
  p->tableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
  p->tableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
  p->tableView->setShowGrid(false);

  p->tableView->verticalHeader()->hide();
  QHeaderView* verticalHeader = p->tableView->verticalHeader();
  // verticalHeader->setResizeMode(QHeaderView::Fixed);
  verticalHeader->setDefaultSectionSize(22);

  p->tableView->setMaximumWidth(400);
  p->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

  p->stackedWidget = new QStackedWidget();

  QHBoxLayout* l = new QHBoxLayout();

  l->addWidget(p->tableView);
  l->addWidget(p->stackedWidget);

  setLayout(l);
}


void
SettingsWidget::
connectSignals(SettingsWidgetModel* tableModel)
{
  connect(p->tableView, SIGNAL(activated(const QModelIndex &)),
          this,         SLOT(onConnectionClicked(const QModelIndex &)));

  // TODO "click on first row"
  p->tableView->selectRow(0);
}


void
SettingsWidget::
onConnectionClicked(const QModelIndex& index)
{
  //
  Q_UNUSED(index);
}
