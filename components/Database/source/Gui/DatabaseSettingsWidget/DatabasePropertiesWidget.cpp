#include "DatabasePropertiesWidget.hpp"

#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHeaderView>

#include <Models/DatabaseSettingsWidgetModel/DatabasePropertiesWidgetModel.hpp>

using Geo::Database::Connections::Connection;
using Geo::Database::Gui::DatabaseSettingsWidget::DatabasePropertiesWidget;
using Geo::Database::Models::DatabaseSettingsWidgetModel::DatabasePropertiesWidgetModel;

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
}

void
DatabasePropertiesWidget::
createUi()
{
  _p->propertiesWidgetModel = new DatabasePropertiesWidgetModel();

  //--------------

  _p->traitsTable = new QTableView();
  _p->traitsTable->horizontalHeader()->setStretchLastSection(true);
  _p->traitsTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
  _p->traitsTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);

  _p->traitsTable->setModel(_p->propertiesWidgetModel);

  QVBoxLayout* l = new QVBoxLayout();

  l->addWidget(_p->traitsTable);

  setLayout(l);
}
