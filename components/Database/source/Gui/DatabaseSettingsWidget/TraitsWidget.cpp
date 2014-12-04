#include "TraitsWidget.hpp"
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>

#include <Gui/DatabaseSettingsWidget/WellTraitItemDelegate.hpp>
#include <Models/DatabaseSettingsWidgetModel/TraitsWidgetModel.hpp>

#include <Models/DatabaseSettingsWidgetModel/WellTraitEntry.hpp>

using Geo::Database::Connections::Connection;
using Geo::Database::Gui::DatabaseSettingsWidget::TraitsWidget;
using Geo::Database::Models::DatabaseSettingsWidgetModel::
      TraitsWidgetModel;

using Geo::Database::Gui::DatabaseSettingsWidget::WellTraitItemDelegate;

struct TraitsWidget::Private
{
  QTableView* traitsTable;

  TraitsWidgetModel* traitsWidgetModel;

  Connections::Connection::Shared c;
};

TraitsWidget::
TraitsWidget():
  _p(new Private)
{
  createUi();
  connectSignals();
}


TraitsWidget::
~TraitsWidget()
{
  delete _p;

  // TODO: check delete models everywhere
  delete _p->traitsWidgetModel;
}


void
TraitsWidget::
setConnection(Connections::Connection::Shared connection)
{
  _p->c = connection;

  _p->traitsWidgetModel->setConnection(connection);
}


void
TraitsWidget::
createUi()
{
  using Models::DatabaseSettingsWidgetModel::WellTraitEntry;
  _p->traitsWidgetModel = new TraitsWidgetModel();

  // --------------

  _p->traitsTable = new QTableView();

  _p->traitsTable->setModel(_p->traitsWidgetModel);

  // temporarily use standard edit tool
  _p->traitsTable->setItemDelegate(new WellTraitItemDelegate());

  auto headerView = _p->traitsTable->horizontalHeader();

  headerView->setStretchLastSection(false);
  headerView->setSectionResizeMode(WellTraitEntry::Trait,
                                   QHeaderView::ResizeToContents);

  headerView->setSectionResizeMode(WellTraitEntry::Synonyms,
                                   QHeaderView::ResizeToContents);

  headerView->setSectionResizeMode(WellTraitEntry::Type,
                                   QHeaderView::Stretch);

  headerView->setSectionResizeMode(WellTraitEntry::CloseAction,
                                   QHeaderView::Fixed);
  headerView->resizeSection(WellTraitEntry::CloseAction, 20);

  auto verticalHeader = _p->traitsTable->verticalHeader();
  verticalHeader->setSectionResizeMode(QHeaderView::ResizeToContents);
  verticalHeader->hide();

  _p->traitsTable->setEditTriggers(QAbstractItemView::AllEditTriggers);

  QVBoxLayout* l = new QVBoxLayout();

  l->setContentsMargins(0, 0, 0, 0);

  l->addWidget(_p->traitsTable);

  setLayout(l);
}


void
TraitsWidget::
connectSignals()
{
  // for deleting rows
  connect(_p->traitsTable, SIGNAL(clicked(const QModelIndex &)),
          _p->traitsWidgetModel,   SLOT(onClicked(const QModelIndex &)));
}
