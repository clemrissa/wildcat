#ifndef Geo_Database_DatabaseSettingsWidget_hpp
#define Geo_Database_DatabaseSettingsWidget_hpp

#include <QWidget>

namespace Geo {
namespace Database {
namespace Models {
namespace SettingsWidgetModel {
class SettingsWidgetModel;
}
}

namespace Gui {
class DatabaseSettingsWidget: public QWidget
{
  Q_OBJECT

public:
  DatabaseSettingsWidget(Models::SettingsWidgetModel::SettingsWidgetModel*
                         tableModel);

  ~DatabaseSettingsWidget();

public slots:
  void
  onConnectionClicked(const QModelIndex& index);

private:
  void
  setupUi(
    Models::SettingsWidgetModel::SettingsWidgetModel* tableModel);

  void
  connectSignals(
    Models::SettingsWidgetModel::SettingsWidgetModel* tableModel);

private:
  struct Private;

  Private* p;
};
}
}
}

#endif // Geo_Database_DatabaseSettingsWidget_hpp
