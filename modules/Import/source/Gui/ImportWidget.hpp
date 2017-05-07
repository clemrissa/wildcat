#pragma once

#include <QtWidgets/QWidget>

#include <Database/Mixin/ConnectionAcceptor>

namespace Geo {
namespace Import {
//

class ImportTreeModel;

namespace Gui {
//

class ImportWidget : public QWidget
{
  Q_OBJECT

public:
  ImportWidget();

  virtual
  ~ImportWidget();

public:
  void
  setModel(ImportTreeModel* importModel);

private slots:
  void
  onImportClicked();

  void
  onConnectionSelected(int index);

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

  Private* p;
};

//
} // namespace Gui
} // namespace Import
} // namespace Geo
