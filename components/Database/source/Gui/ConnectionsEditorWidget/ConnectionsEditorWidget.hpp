#ifndef Geo_Database_ConnectionsEditorWidget_hpp
#define Geo_Database_ConnectionsEditorWidget_hpp

#include <QWidget>

namespace Geo {
namespace Database {
namespace Models {
namespace ConnectionsEditorWidgetModel {
class ConnectionsEditorWidgetModel;
}
}

namespace Gui {
namespace ConnectionsEditorWidget {
//

class ConnectionsEditorWidget: public QWidget
{
  Q_OBJECT

public:
  ConnectionsEditorWidget(
    Models::ConnectionsEditorWidgetModel::ConnectionsEditorWidgetModel*
    treeModel);

  ~ConnectionsEditorWidget();

public slots:
  void
  onConnectionClicked(const QModelIndex& index);

private:
  void
  setupUi(
    Models::ConnectionsEditorWidgetModel::ConnectionsEditorWidgetModel* treeModel);

  void
  connectSignals(
    Models::ConnectionsEditorWidgetModel::ConnectionsEditorWidgetModel* treeModel);

private:
  struct Private;

  Private* p;
};

//
}
}
}
}

#endif //  Geo_Database_ConnectionsEditorWidget_hpp
