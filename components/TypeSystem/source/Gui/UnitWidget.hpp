#ifndef Geo_Import_UnitWidget_hpp
#define Geo_Import_UnitWidget_hpp

#include <Database/Mixin/ConnectionAcceptor>
#include <QWidget>

namespace Geo {
namespace TypeSystem {
namespace Gui {
//

class UnitWidget:
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

#endif // Geo_Import_UnitWidget_hpp
