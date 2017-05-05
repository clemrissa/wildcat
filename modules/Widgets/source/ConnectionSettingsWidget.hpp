#ifndef Geo_Widgets_ConnectionSettingsWidget_hpp
#define Geo_Widgets_ConnectionSettingsWidget_hpp

#include <QtWidgets/QWidget>

#include <Database/Connections/Connection>

namespace Geo {
namespace Widgets {
//

class ConnectionSettingsWidget: public QWidget
{
  // Q_OBJECT

public:
  virtual
  ~ConnectionSettingsWidget()
  {
  }

  virtual void
  setEditorWidget(QWidget* editorWidget) = 0;

signals:
  virtual
  void connectionChanged(Database::Connections::Connection::Shared) = 0;
};

//
}
}
#endif //  Geo_Widgets_ConnectionSettingsWidget_hpp
