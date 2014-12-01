#include "SQLiteConnectionPropertiesWidget.hpp"

#include <QtWidgets/QFileDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

#include <QtCore/QSharedPointer>

#include <DependencyManager/ApplicationContext>

#include <Uni/Logging/Logging>

#include <Widgets/KeywordWidget>

#include <QDebug>

using Geo::Database::Connections::Connection;
using Geo::Database::Connections::SQLiteConnection;
using Geo::Database::Gui::SQLiteConnectionPropertiesWidget;

struct SQLiteConnectionPropertiesWidget::Private
{
  QPushButton* openButton;
  QPushButton* createButton;
  QLineEdit*   databasePath;

  QSharedPointer<SQLiteConnection> c;
};

SQLiteConnectionPropertiesWidget::
SQLiteConnectionPropertiesWidget():
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
setConnection(Connection::Shared connection)
{
  p->c = connection.staticCast<SQLiteConnection>();

  p->databasePath->setText(p->c->database());

  connect(p->c.data(), SIGNAL(databaseChanged(QString)),
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

  if (!p->c.isNull())
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

  if (!p->c.isNull())
    p->c->setDatabase(fileName);
}
