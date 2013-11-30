#include "DatabaseUiFactory.hpp"

#include <QDockWidget>

#include "Auxiliary/ExecutionControl.hpp"

// ---

using Geo::Database::Private::DatabaseUiFactory;

DatabaseUiFactory::
DatabaseUiFactory() {
  DEBUG << "DatabaseUiFactory is being created";
}

DatabaseUiFactory::
~DatabaseUiFactory() {
  DEBUG << "DatabaseUiFactory is being destroyed";
}

Q_INVOKABLE QDockWidget*
DatabaseUiFactory::
createConnectionListView(QObject* value) const {
  qmlRegisterType<Connection>("Connection", 1, 0, "Connection");

  QQuickView*  view    = new QQuickView();
  QQmlContext* context = view->engine()->rootContext();

  context->setContextProperty("ConnectionListModel", value);
  view->setSource(QUrl::fromLocalFile(
                    QString(
                      "%1/../components/Database/ConnectionListView.qml").arg(
                      QCoreApplication::applicationDirPath())));
  view->setResizeMode(QQuickView::SizeRootObjectToView);

  QWidget* widget = QWidget::createWindowContainer(view);
  widget->setFocusPolicy(Qt::TabFocus);

  auto dockWidget = new QDockWidget(tr("Database Connections"));
  dockWidget->setWidget(widget);

  return dockWidget;
}
