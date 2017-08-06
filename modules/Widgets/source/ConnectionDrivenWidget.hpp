#pragma once

#include <memory>

#include "IConnectionDrivenWidget.hpp"

#include "WidgetsExport.hpp"

namespace Geo
{
namespace Widgets
{

/// This is a container class displaying a combobox with connections and
/// a user-defined child Widget with some connection-related data
class Widgets_PUBLIC ConnectionDrivenWidget : public IConnectionDrivenWidget
{
  Q_OBJECT

public:
  Q_INVOKABLE
  ConnectionDrivenWidget();

  virtual
  ~ConnectionDrivenWidget();

  virtual void
  setEditorWidget(QWidget* editorWidget) override;

private slots:

  void
  onOkClicked();

  void
  onConnectionActivated(int index);

signals:

  void
  connectionChanged(std::shared_ptr<Database::IConnection>) override;

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
}
}
