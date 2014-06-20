#include "DatabasePropertiesWidget.hpp"

#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QPushButton>

using Geo::Database::Connections::Connection;
using Geo::Database::Gui::DatabasePropertiesWidget;

struct DatabasePropertiesWidget::Private {
  QPushButton* openButton;
  QPushButton* createButton;
  QLineEdit*   databasePath;
};

DatabasePropertiesWidget::
DatabasePropertiesWidget()
{
  //
}


DatabasePropertiesWidget::
~DatabasePropertiesWidget()
{
  //
}


void
DatabasePropertiesWidget::
setConnection(Connections::Connection::Shared connection)
{
  //
}


void
DatabasePropertiesWidget::
createUi()
{
  //
}
