#ifndef Geo_Database_DatabaseSettingsWidget_hpp
#define Geo_Database_DatabaseSettingsWidget_hpp

#include <QWidget>

namespace Geo {
//

namespace Database {
namespace Gui {
namespace DatabaseSettingsWidget {
//

class DatabaseSettingsWidget: public QWidget
{
  Q_OBJECT

public:
  DatabaseSettingsWidget();

  virtual
  ~DatabaseSettingsWidget();

public slots:
  void
  onOkClicked();

  void
  onConnectionActivated(int index);

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
} // Models
} // Database
} // Geo

#endif // Geo_Database_DatabaseSettingsWidget_hpp
