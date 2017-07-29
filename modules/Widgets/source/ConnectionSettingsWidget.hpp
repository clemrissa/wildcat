#pragma once

#include "IConnectionSettingsWidget.hpp"

#include "WidgetsExport.hpp"

namespace Geo
{
namespace Widgets
{
//

class Widgets_PUBLIC ConnectionSettingsWidget : public IConnectionSettingsWidget
{
  Q_OBJECT

public:
  Q_INVOKABLE
  ConnectionSettingsWidget();

  virtual
  ~ConnectionSettingsWidget();

  virtual void
  setEditorWidget(QWidget* editorWidget) override;

private slots:

  void
  onOkClicked();

  void
  onConnectionActivated(int index);

signals:

  void connectionChanged(std::shared_ptr<Database::IConnection>) override;

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
}
}
