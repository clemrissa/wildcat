#pragma once

#include <QtWidgets/QWidget>

#include <Database/Mixin/ConnectionAcceptor>

namespace Geo
{

using Database::IConnection;

namespace Import
{
//

class ImportTreeModel;

namespace Gui
{
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
  setConnection(std::shared_ptr<IConnection> connection) override;

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
