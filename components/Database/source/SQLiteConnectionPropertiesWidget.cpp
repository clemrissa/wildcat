#include "SQLiteConnectionPropertiesWidget.hpp"

#include <QFileDialog>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

#include <QSharedPointer>

using Geo::Database::SQLiteConnectionPropertiesWidget;

struct SQLiteConnectionPropertiesWidget::Private {
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
  p->openButton = new QPushButton(QIcon(":/open.png"), tr("Open"));

  p->createButton = new QPushButton(QIcon(":/new_file.png"), tr("Create"));

  p->databasePath = new QLineEdit();

  p->databasePath->setReadOnly(true);

  QHBoxLayout* l = new QHBoxLayout();

  l->addWidget(p->openButton);
  l->addWidget(p->createButton);
  l->addWidget(p->databasePath);

  QVBoxLayout* ll = new QVBoxLayout();

  ll->addLayout(l);
  ll->addStretch();

  this->setLayout(ll);

  // ---------------------

  connect(p->openButton, SIGNAL(released()),
          this, SLOT(onOpenClicked()));

  connect(p->createButton, SIGNAL(released()),
          this, SLOT(onNewClicked()));
}


void
SQLiteConnectionPropertiesWidget::
onOpenClicked()
{
  //

  QString fileName = QFileDialog::getOpenFileName(this, tr("Select a database file"),
                                                  QString(), tr("Database files (*.db)"));

  if (fileName.isEmpty())
    return;

  if (!p->c.isNull())
    p->c->setDatabase(fileName);
}


void
SQLiteConnectionPropertiesWidget::
onNewClicked()
{
  QString fileName = QFileDialog::getSaveFileName(this, tr("Create a database file"),
                                                  QString(), tr("Database files (*.db)"));

  if (fileName.isEmpty())
    return;

  if (!p->c.isNull())
    p->c->setDatabase(fileName);
}
