#ifndef Geo_Widgets_Implementation_ConnectionSettingsWidget_hpp
#define Geo_Widgets_Implementation_ConnectionSettingsWidget_hpp

#include <ConnectionSettingsWidget.hpp>

namespace Geo {
namespace Widgets {
namespace Implementation {
//

class ConnectionSettingsWidget:
  public Geo::Widgets::ConnectionSettingsWidget
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
  void connectionChanged(Database::Connections::Connection::Shared) override;

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
}
#endif //  Geo_Widgets_Implementation_ConnectionSettingsWidget_hpp