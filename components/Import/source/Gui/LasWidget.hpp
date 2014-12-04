#ifndef Geo_Import_LasWidget_hpp
#define Geo_Import_LasWidget_hpp

#include <QtWidgets/QWidget>

#include <Database/Mixin/ConnectionAcceptor>

namespace Geo {
namespace Import {
//

class ImportTreeModel;

namespace Gui {
//

class LasWidget: 
  public QWidget,
  public Database::Mixin::ConnectionAcceptor 
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
  setConnection(Database::Connections::Connection::Shared connection) override;

private slots:
  //void
  //onImportClicked();

  //void
  //onConnectionSelected(int index);

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

#endif // Geo_Import_LasWidget_hpp
