#pragma once

#include <Database/Mixin/ConnectionAcceptor>
#include <QWidget>

namespace Geo {
namespace TypeSystem {
namespace Gui {
//

class CurveTypeWidget :
  public QWidget,
  public Database::Mixin::ConnectionAcceptor
{
  Q_OBJECT

public:
  CurveTypeWidget();

  virtual
  ~CurveTypeWidget();

public slots:
  void
  setConnection(Database::Connection::Shared connection) override;

private slots:
  void
  onTableViewMenuRequested(const QPoint&);

  void
  onLoadSlbXmlClicked();

  void
  onSaveGeoXmlClicked();

  void
  onLoadGeoXmlClicked();

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
