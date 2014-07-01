#include "DatabasePropertiesWidget.hpp"

#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>

#include <Gui/DatabaseSettingsWidget/WellTraitItemDelegate.hpp>
#include <Models/DatabaseSettingsWidgetModel/DatabasePropertiesWidgetModel.hpp>

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
  _p->propertiesWidgetModel = new DatabasePropertiesWidgetModel();

  // --------------

  _p->traitsTable = new QTableView();

  _p->traitsTable->setModel(_p->propertiesWidgetModel);

  // _p->traitsTable->setItemDelegate(new WellTraitItemDelegate());

  auto headerView = _p->traitsTable->horizontalHeader();

  headerView->setStretchLastSection(false);
  headerView->setSectionResizeMode(0, QHeaderView::ResizeToContents);
  headerView->setSectionResizeMode(1, QHeaderView::Stretch);
  headerView->setSectionResizeMode(2, QHeaderView::Fixed);
  headerView->resizeSection(2, 20);

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
