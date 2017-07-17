#pragma once

#include <QWidget>

namespace Geo
{
namespace Database
{
namespace Models
{
class ConnectionsEditorWidgetModel;
}

namespace Gui
{
namespace ConnectionsEditorWidget
{
//

// Shows dialog for editing connections
class ConnectionsEditorWidget : public QWidget
{
  Q_OBJECT

public:
  ConnectionsEditorWidget(Models::ConnectionsEditorWidgetModel* treeModel);

  ~ConnectionsEditorWidget();

public slots:
  void
  onConnectionClicked(const QModelIndex& index);

private:
  void
  setupUi(Models::ConnectionsEditorWidgetModel* treeModel);

  void
  connectSignals(Models::ConnectionsEditorWidgetModel* treeModel);

private:
  struct Private;

  Private* p;
};

//
}
}
}
}
