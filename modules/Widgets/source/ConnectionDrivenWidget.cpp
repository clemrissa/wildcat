#include "ConnectionDrivenWidget.hpp"

#include <QtCore/QAbstractItemModel>

#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

#include <ComponentManager/Creator>

#include <Models/ConnectionListModel>

#include <Database/Connections/IConnectionManager>

using Geo::Widgets::ConnectionDrivenWidget;

struct ConnectionDrivenWidget::Private
{
  QComboBox* connectionsComboBox = nullptr;

  QGroupBox* groupBox = nullptr;

  QWidget* editorWidget = nullptr;

  QDialogButtonBox* dialogButton = nullptr;

  std::unique_ptr<QAbstractItemModel> model;
};

ConnectionDrivenWidget::
ConnectionDrivenWidget()
  : p(std::make_unique<Private>())
{
  setupUi();
  connectSignals();
}


ConnectionDrivenWidget::
~ConnectionDrivenWidget()
{}

void
ConnectionDrivenWidget::
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
  using Database::IConnectionManager;

  auto cm =
    ComponentManager::create<IConnectionManager*>("Database.ConnectionManager");

  if (cm->size() > 0)
    emit connectionChanged(cm->connections()[0]);
}


void
ConnectionDrivenWidget::
setupUi()
{
  setWindowTitle(tr("Editor Widget"));
  setMinimumSize(800, 400);

  // ---
  p->connectionsComboBox = new QComboBox();

  using CLM = Geo::Models::ConnectionListModel;

  auto m = ComponentManager::create<CLM*>("Models.ConnectionListModel");
  p->model.reset(m);

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
ConnectionDrivenWidget::
connectSignals()
{
  connect(p->connectionsComboBox, SIGNAL(activated(int)),
          this, SLOT(onConnectionActivated(int)));

  connect(p->dialogButton, SIGNAL(accepted()),
          this, SLOT(onOkClicked()));

  if (p->editorWidget)
    connect(this,
            SIGNAL(connectionChanged(std::shared_ptr<Database::IConnection>)),
            p->editorWidget,
            SLOT(setConnection(std::shared_ptr<Database::IConnection>)));
}


void
ConnectionDrivenWidget::
onOkClicked()
{
  // close import window
  static_cast<QWidget*>(parent())->close();
}


void
ConnectionDrivenWidget::
onConnectionActivated(int index)
{
  using CM = Database::IConnectionManager;

  auto cm = ComponentManager::create<CM*>("Database.ConnectionManager");

  emit connectionChanged(cm->connections()[index]);
}
