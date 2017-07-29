#pragma once

#include <QtWidgets/QWidget>

#include <Database/Mixin/ConnectionAcceptor>

namespace Geo
{

using Database::IConnection;

namespace TypeSystem
{
namespace Gui
{
//

class CurveTypeWidget
  : public QWidget
{
  Q_OBJECT

public:
  CurveTypeWidget();

  virtual
  ~CurveTypeWidget();

public slots:

  void
  setConnection(std::shared_ptr<Database::IConnection> connection);

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
