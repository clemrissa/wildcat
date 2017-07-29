#pragma once

#include <Database/Mixin/ConnectionAcceptor>

#include <QtWidgets/QWidget>

namespace Geo
{

using Database::IConnection;

namespace TypeSystem
{
namespace Gui
{
//

class UnitWidget
  : public QWidget
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
  setConnection(std::shared_ptr<Database::IConnection> connection);

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
