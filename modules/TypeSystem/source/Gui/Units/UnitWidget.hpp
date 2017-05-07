#pragma once

#include <Database/Mixin/ConnectionAcceptor>
#include <QWidget>

namespace Geo {
namespace TypeSystem {
namespace Gui {
//

class UnitWidget :
  public QWidget,
  public Database::Mixin::ConnectionAcceptor
{
  Q_OBJECT

public:
  UnitWidget();

  virtual
  ~UnitWidget();

private slots:
  void
  onTableViewMenuRequested(const QPoint&);

  void
  onLoadXmlClicked();

  void
  onSaveXmlClicked();

public slots:
  void
  setConnection(Database::Connections::Connection::Shared connection) override;

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
} // namespace TypeSystem
} // namespace Geo
