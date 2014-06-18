#ifndef Geo_Database_ConnectionsWidget_hpp
#define Geo_Database_ConnectionsWidget_hpp

#include <QWidget>

namespace Geo {
namespace Database {
namespace Models {
namespace ConnectionsWidgetModel {
class ConnectionsWidgetModel;
}
}

namespace Gui {
class ConnectionsWidget: public QWidget {
  Q_OBJECT

public:
  ConnectionsWidget(Models::ConnectionsWidgetModel::ConnectionsWidgetModel* treeModel);

  ~ConnectionsWidget();

public slots:
  void
  onConnectionClicked(const QModelIndex& index);

private:
  void
  setupUi(Models::ConnectionsWidgetModel::ConnectionsWidgetModel* treeModel);

  void
  connectSignals(Models::ConnectionsWidgetModel::ConnectionsWidgetModel* treeModel);

private:
  struct Private;

  Private* p;
};
}
}
}

#endif //  Geo_Database_ConnectionsWidget_hpp
