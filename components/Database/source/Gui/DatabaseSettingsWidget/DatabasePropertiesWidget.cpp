#include "DatabasePropertiesWidget.hpp"

#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>

#include <Gui/DatabaseSettingsWidget/WellTraitItemDelegate.hpp>
#include <Models/DatabaseSettingsWidgetModel/DatabasePropertiesWidgetModel.hpp>

#include <Models/DatabaseSettingsWidgetModel/WellTraitEntry.hpp>

using Geo::Database::Connections::Connection;
using Geo::Database::Gui::DatabaseSettingsWidget::DatabasePropertiesWidget;
using Geo::Database::Models::DatabaseSettingsWidgetModel::
      DatabasePropertiesWidgetModel;

using Geo::Database::Gui::DatabaseSettingsWidget::WellTraitItemDelegate;

struct DatabasePropertiesWidget::Private
{
  QTableView* traitsTable;

  DatabasePropertiesWidgetModel* propertiesWidgetModel;

  Connections::Connection::Shared c;
};

DatabasePropertiesWidget::
DatabasePropertiesWidget():
  _p(new Private)
{
  createUi();
  connectSignals();
}


DatabasePropertiesWidget::
~DatabasePropertiesWidget()
{
  delete _p;

  delete _p->propertiesWidgetModel;
}


void
DatabasePropertiesWidget::
setConnection(Connections::Connection::Shared connection)
{
  _p->c = connection;

  _p->propertiesWidgetModel->setConnection(connection);
}


void
DatabasePropertiesWidget::
createUi()
{
  using Models::DatabaseSettingsWidgetModel::WellTraitEntry;
  _p->propertiesWidgetModel = new DatabasePropertiesWidgetModel();

  // --------------

  _p->traitsTable = new QTableView();

  _p->traitsTable->setModel(_p->propertiesWidgetModel);

  // temporarily use standard edit tool
  _p->traitsTable->setItemDelegate(new WellTraitItemDelegate());

  auto headerView = _p->traitsTable->horizontalHeader();

  headerView->setStretchLastSection(false);
  headerView->setSectionResizeMode(WellTraitEntry::Trait,
                                   QHeaderView::ResizeToContents);
  headerView->setSectionResizeMode(WellTraitEntry::Synonyms,
                                   QHeaderView::Stretch);
  headerView->setSectionResizeMode(WellTraitEntry::Type,
                                   QHeaderView::Stretch);

  headerView->setSectionResizeMode(WellTraitEntry::CloseAction,
                                   QHeaderView::Fixed);
  headerView->resizeSection(WellTraitEntry::CloseAction, 20);

  QHeaderView* verticalHeader = _p->traitsTable->verticalHeader();
  verticalHeader->setSectionResizeMode(QHeaderView::ResizeToContents);
  verticalHeader->hide();

  _p->traitsTable->setEditTriggers(QAbstractItemView::AllEditTriggers);

  QVBoxLayout* l = new QVBoxLayout();

  l->addWidget(_p->traitsTable);

  setLayout(l);
}


void
DatabasePropertiesWidget::
connectSignals()
{
  // for deleting rows
  connect(_p->traitsTable, SIGNAL(clicked(const QModelIndex &)),
          _p->propertiesWidgetModel,   SLOT(onClicked(const QModelIndex &)));
}
