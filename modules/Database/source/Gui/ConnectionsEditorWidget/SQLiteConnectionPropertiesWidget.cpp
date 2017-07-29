#include "SQLiteConnectionPropertiesWidget.hpp"

#include <QtWidgets/QFileDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

#include <QtCore/QDebug>

#include <memory>

#include <ComponentManager/Creator>

#include <Widgets/KeywordWidget>

using Geo::Database::IConnection;
using Geo::Database::SQLiteConnection;
using Geo::Database::Gui::SQLiteConnectionPropertiesWidget;

struct SQLiteConnectionPropertiesWidget::Private
{
  QPushButton* openButton;
  QPushButton* createButton;
  QLineEdit* databasePath;

  std::shared_ptr<SQLiteConnection> c;
};

SQLiteConnectionPropertiesWidget::
SQLiteConnectionPropertiesWidget() :
  p(new Private)
{
  createUi();
  connectSignals();
}


SQLiteConnectionPropertiesWidget::
~SQLiteConnectionPropertiesWidget()
{
  delete p;
}


void
SQLiteConnectionPropertiesWidget::
setConnection(std::shared_ptr<IConnection> connection)
{
  p->c = std::static_pointer_cast<SQLiteConnection>(connection);

  p->databasePath->setText(p->c->database());

  connect(p->c.get(), SIGNAL(databaseChanged(QString)),
          p->databasePath, SLOT(setText(QString)));
}


void
SQLiteConnectionPropertiesWidget::
createUi()
{
  p->openButton = new QPushButton(QIcon(":/open.png"), QString());

  p->openButton->setToolTip(tr("Open"));

  p->createButton = new QPushButton(QIcon(":/new_file.png"), QString());

  p->createButton->setToolTip(tr("Create"));

  p->databasePath = new QLineEdit();

  p->databasePath->setReadOnly(true);

  QVBoxLayout* ll = new QVBoxLayout(this);

  QHBoxLayout* l = new QHBoxLayout();

  l->addWidget(p->openButton);
  l->addWidget(p->createButton);
  l->addWidget(p->databasePath);

  ll->addLayout(l);
  ll->addStretch();
}


void
SQLiteConnectionPropertiesWidget::
connectSignals()
{
  connect(p->openButton, SIGNAL(released()),
          this, SLOT(onOpenClicked()));

  connect(p->createButton, SIGNAL(released()),
          this, SLOT(onNewClicked()));
}


void
SQLiteConnectionPropertiesWidget::
onOpenClicked()
{
  QString fileName =
    QFileDialog::getOpenFileName(this, tr("Select a database file"),
                                 QString(),
                                 tr("Database files (*.db)"));

  if (fileName.isEmpty())
    return;

  if (p->c)
    p->c->setDatabase(fileName);
}


void
SQLiteConnectionPropertiesWidget::
onNewClicked()
{
  QString fileName =
    QFileDialog::getSaveFileName(this, tr("Create a database file"),
                                 QString(),
                                 tr("Database files (*.db)"));

  if (fileName.isEmpty())
    return;

  if (p->c)
    p->c->setDatabase(fileName);
}
