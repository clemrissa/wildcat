#include "DatabaseSettingsWidget.hpp"

#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>

#include <Connections/ConnectionManager.hpp>
#include <DependencyManager/ApplicationContext>

#include <Uni/Logging/Logging>

#include <Models/ConnectionListModel>

#include <Gui/DatabaseSettingsWidget/DatabasePropertiesWidget.hpp>

using AC = DependencyManager::ApplicationContext;
using Geo::Database::Gui::DatabaseSettingsWidget::DatabasePropertiesWidget;
using Geo::Database::Gui::DatabaseSettingsWidget::DatabaseSettingsWidget;

struct DatabaseSettingsWidget::Private
{
  QComboBox* connectionsComboBox;

  DatabasePropertiesWidget* traitsWidget;

  QDialogButtonBox* dialogButton;
};

DatabaseSettingsWidget::
DatabaseSettingsWidget():
  p(new DatabaseSettingsWidget::Private())
{
  setupUi();
  connectSignals();
}


DatabaseSettingsWidget::
~DatabaseSettingsWidget()
{
  delete p;
}


void
DatabaseSettingsWidget::
setupUi()
{
  setWindowTitle(tr("Well Traits"));
  setMinimumSize(800, 400);

  // ----------- combo box with connections

  p->connectionsComboBox = new QComboBox();

  using CLM = Geo::Models::ConnectionListModel;
  auto m = AC::create<CLM>("Models.ConnectionListModel");

  p->connectionsComboBox->setModel(m);

  // -----------------

  p->traitsWidget = new DatabasePropertiesWidget();

  //
  p->dialogButton = new QDialogButtonBox(QDialogButtonBox::Ok);

  // auto okButton = p->dialogButton->button(QDialogButtonBox::Ok);
  // okButton->setText(tr("Import"));

  // QHBoxLayout* l = new QHBoxLayout();
  auto l = new QVBoxLayout();

  l->addWidget(p->connectionsComboBox);
  l->addWidget(p->traitsWidget);
  l->addWidget(p->dialogButton);

  setLayout(l);

  // select first connection
}


void
DatabaseSettingsWidget::
connectSignals()
{
  connect(p->connectionsComboBox, SIGNAL(activated(int)),
          this, SLOT(onConnectionActivated(int)));

  connect(p->dialogButton, SIGNAL(accepted()),
          this, SLOT(onOkClicked()));

  // "click on first row in connections list
  using Connections::ConnectionManager;

  auto cm = AC::create<ConnectionManager>(
    "Database.ConnectionManager");

  if (cm->size() > 0) {
    auto connections = cm->connections();
    p->traitsWidget->setConnection(connections[0]);
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
onConnectionActivated(int index)
{
  using CM = Connections::ConnectionManager;

  auto cm = AC::create<CM>("Database.ConnectionManager");

  p->traitsWidget->setConnection(cm->connections()[index]);
}
