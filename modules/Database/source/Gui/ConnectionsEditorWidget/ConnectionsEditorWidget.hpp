#pragma once

#include <memory>

#include <QtWidgets/QWidget>

namespace Geo
{
namespace Database
{
namespace Gui
{

class ConnectionsEditorWidgetModel;

namespace ConnectionsEditorWidget
{
//

// Shows dialog for editing connections
class ConnectionsEditorWidget final : public QWidget
{
  Q_OBJECT

public:
  ConnectionsEditorWidget(ConnectionsEditorWidgetModel* treeModel);

  ~ConnectionsEditorWidget();

public slots:

  void
  onConnectionClicked(const QModelIndex& index);

private:

  void
  setupUi(Gui::ConnectionsEditorWidgetModel* treeModel);

  void
  connectSignals(Gui::ConnectionsEditorWidgetModel* treeModel);

private:
  struct Private;

  std::unique_ptr<Private> p;
};

//
}
}
}
}
