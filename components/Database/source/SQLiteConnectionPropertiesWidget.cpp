#include "SQLiteConnectionPropertiesWidget.hpp"

#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

using Geo::Database::SQLiteConnectionPropertiesWidget;

struct SQLiteConnectionPropertiesWidget::Private {
  QPushButton* openButton;
  QPushButton* createButton;
  QLineEdit*   databasePath;
};

SQLiteConnectionPropertiesWidget::
SQLiteConnectionPropertiesWidget():
  p(new Private) {
  createUi();
}

SQLiteConnectionPropertiesWidget::
~SQLiteConnectionPropertiesWidget() {
  delete p;
}

void
SQLiteConnectionPropertiesWidget::
createUi() {
  p->openButton = new QPushButton(QIcon(":/open.png"), tr("Open"));

  p->createButton = new QPushButton(QIcon(":/new_file.png"), tr("Create"));

  p->databasePath = new QLineEdit();

  QHBoxLayout* l = new QHBoxLayout();

  l->addWidget(p->openButton);
  l->addWidget(p->createButton);
  l->addWidget(p->databasePath);

  QVBoxLayout* ll = new QVBoxLayout();

  ll->addLayout(l);
  ll->addStretch();

  this->setLayout(ll);
}
