#pragma once

#include <QtWidgets/QWidget>

#include <Database/Mixin/ConnectionAcceptor>

namespace Geo {
namespace Import {
//

class ImportTreeModel;

namespace Gui {
//

class LasWidget
  : public QWidget
  , public Database::Mixin::ConnectionAcceptor
{
  Q_OBJECT

public:
  LasWidget();

  virtual
  ~LasWidget();

public:
  void
  setModel(ImportTreeModel* importModel);

  void
  setConnection(Database::Connection::Shared connection) override;

private slots:
  void
  onTableViewMenuRequested(const QPoint&);

signals:
  void notifyMainWindow(QString);

private:
  void
  setupUi();

  void
  connectSignals();

private:
  struct Private;

  Private* _p;
};

//
} // namespace Gui
} // namespace Import
} // namespace Geo
