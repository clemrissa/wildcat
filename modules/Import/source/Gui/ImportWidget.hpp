#pragma once

#include <memory>

#include <QtWidgets/QWidget>

#include <Database/Mixin/ConnectionAcceptor>

namespace Geo
{
namespace Import
{
//

class ImportTreeModel;

namespace Gui
{
//

class ImportWidget : public QWidget
{
  Q_OBJECT

public:
  ImportWidget();

  virtual
  ~ImportWidget();

public:

  /// Model is set in ImportController
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

  std::unique_ptr<Private> p;
};

//
} // namespace Gui
} // namespace Import
} // namespace Geo
