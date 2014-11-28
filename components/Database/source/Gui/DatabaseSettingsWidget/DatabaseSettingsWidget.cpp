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
#include <Models/ConnectionTableModel>

#include <Gui/DatabaseSettingsWidget/DatabasePropertiesWidget.hpp>

using Geo::Database::Gui::DatabaseSettingsWidget::DatabaseSettingsWidget;
using Geo::Database::Gui::DatabaseSettingsWidget::DatabasePropertiesWidget;
using DependencyManager::ApplicationContext;

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

  using Geo::Models::ConnectionListModel;
  auto m = 
    ApplicationContext::create<ConnectionListModel>("Models.ConnectionListModel");


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

  auto connectionsManager =
    ApplicationContext::create<ConnectionManager>("Database.ConnectionManager");

  if (connectionsManager->size() > 0) {
    auto connections =  connectionsManager->connections();
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
  using Connections::ConnectionManager;
  using DependencyManager::ApplicationContext;

  auto connectionsManager =
    ApplicationContext::create<ConnectionManager>("Database.ConnectionManager");

  p->traitsWidget->setConnection(connectionsManager->connections()[index]);
}
