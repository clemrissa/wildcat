#include "DatabaseSettingsWidget.hpp"

#include <QHBoxLayout>
#include <QStackedWidget>
#include <QTreeView>

namespace Geo {
namespace Database {
struct DatabaseSettingsWidget::Private {
  QTreeView*      treeView;
  QStackedWidget* stackedWidget;
};

DatabaseSettingsWidget::
DatabaseSettingsWidget():
  p(new DatabaseSettingsWidget::Private()) {
  setWindowTitle(tr("Database Settings"));
  setMinimumSize(600, 400);

  p->treeView = new QTreeView();

  p->treeView->setMaximumWidth(300);

  p->stackedWidget = new QStackedWidget();

  QHBoxLayout* l = new QHBoxLayout();

  l->addWidget(p->treeView);
  l->addWidget(p->stackedWidget);

  setLayout(l);
}

DatabaseSettingsWidget::
~DatabaseSettingsWidget() {
  delete p;
}
}
}
