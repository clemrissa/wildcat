#ifndef Geo_Import_CurveTypeWidget_hpp
#define Geo_Import_CurveTypeWidget_hpp

#include <QWidget>
#include <Database/Mixin/ConnectionAcceptor>

namespace Geo {
namespace TypeSystem {
namespace Gui {
//

class CurveTypeWidget: 
  public QWidget,
  public Database::Mixin::ConnectionAcceptor

{
  Q_OBJECT

public:
  CurveTypeWidget();

  virtual
  ~CurveTypeWidget();

private slots:
  void
  onTableViewMenuRequested(const QPoint&);

  void 
  onLoadXmlClicked();

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

  Private* p;
};

//
} // namespace Gui
} // namespace TypeSystem
} // namespace Geo

#endif // Geo_Import_CurveTypeWidget_hpp
