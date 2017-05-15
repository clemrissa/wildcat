#include "ConnectionSettingsWidget.hpp"

#include <QtCore/QAbstractItemModel>

#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

#include <ComponentManager/Creator>

#include <Models/ConnectionListModel>

#include <Database/Connections/ConnectionManager>

using Geo::Widgets::Implementation::ConnectionSettingsWidget;

struct ConnectionSettingsWidget::Private
{
  Private() :
    connectionsComboBox(nullptr),
    editorWidget(nullptr),
    dialogButton(nullptr),
    model(nullptr)
  {}

  QComboBox* connectionsComboBox;

  QGroupBox* groupBox;

  QWidget* editorWidget;

  QDialogButtonBox* dialogButton;

  QAbstractItemModel* model;
};

ConnectionSettingsWidget::
ConnectionSettingsWidget() :
  p(new Private())
{
  setupUi();
  connectSignals();
}


ConnectionSettingsWidget::
~ConnectionSettingsWidget()
{
  if (p->model != nullptr)
    delete p->model;

  delete p;
}


void
ConnectionSettingsWidget::
setEditorWidget(QWidget* editorWidget)
{
  // set GUI
  setWindowTitle(editorWidget->windowTitle());
  p->groupBox->setTitle(editorWidget->windowTitle());

  p->editorWidget = editorWidget;

  auto l = static_cast<QVBoxLayout*>(p->groupBox->layout());

  // remove existing widget
  if (l->count())
    delete l->takeAt(0);

  l->addWidget(editorWidget);

  // connect signals
  connectSignals();

  // select first connection
  using Database::Connections::ConnectionManager;

  auto cm = ComponentManager::create<ConnectionManager*>("Database.ConnectionManager");

  if (cm->size() > 0)
    emit connectionChanged(cm->connections()[0]);
}


void
ConnectionSettingsWidget::
setupUi()
{
  setWindowTitle(tr("Editor Widget"));
  setMinimumSize(800, 400);

  // ---
  p->connectionsComboBox = new QComboBox();

  using CLM = Geo::Models::ConnectionListModel;

  auto m = ComponentManager::create<CLM*>("Models.ConnectionListModel");
  p->model = m;

  p->connectionsComboBox->setModel(m);
  // ---

  p->groupBox = new QGroupBox();

  // ---

  p->dialogButton = new QDialogButtonBox(QDialogButtonBox::Ok);

  // auto okButton = p->dialogButton->button(QDialogButtonBox::Ok);
  // okButton->setText(tr("Import"));

  auto l = new QVBoxLayout();

  l->addWidget(p->connectionsComboBox);
  l->addWidget(p->groupBox);

  auto ll = new QVBoxLayout();

  // ll->setContentsMargins(0, 0, 0, 0);

  p->groupBox->setLayout(ll);

  l->addWidget(p->dialogButton);

  setLayout(l);

  // ----
}


void
ConnectionSettingsWidget::
connectSignals()
{
  connect(p->connectionsComboBox, SIGNAL(activated(int)),
          this, SLOT(onConnectionActivated(int)));

  connect(p->dialogButton, SIGNAL(accepted()),
          this, SLOT(onOkClicked()));

  if (p->editorWidget)
    connect(this,
            SIGNAL(connectionChanged(Database::Connections::Connection::Shared)),
            p->editorWidget,
            SLOT(setConnection(Database::Connections::Connection::Shared)));
}


void
ConnectionSettingsWidget::
onOkClicked()
{
  // close import window
  static_cast<QWidget*>(parent())->close();
}


void
ConnectionSettingsWidget::
onConnectionActivated(int index)
{
  using CM = Database::Connections::ConnectionManager;

  auto cm = ComponentManager::create<CM*>("Database.ConnectionManager");

  emit connectionChanged(cm->connections()[index]);
}
