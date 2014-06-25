#include "DatabasePropertiesWidget.hpp"

#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>

using Geo::Database::Connections::Connection;
using Geo::Database::Gui::DatabasePropertiesWidget;

struct DatabasePropertiesWidget::Private
{
  QTableView* traitsTable;

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
  _p->traitsTable = new QTableView();

  QVBoxLayout* l = new QVBoxLayout();

  l->addWidget(_p->traitsTable);

  setLayout(l);
}
