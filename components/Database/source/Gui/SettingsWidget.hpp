#ifndef Geo_Database_SettingsWidget_hpp
#define Geo_Database_SettingsWidget_hpp

#include <QWidget>

namespace Geo {
namespace Database {
class SettingsTreeModel;

namespace Gui {
class SettingsWidget: public QWidget {
  Q_OBJECT

public:
  SettingsWidget(SettingsTreeModel* treeModel);

  ~SettingsWidget();

public slots:
  void
  onTreeClicked(const QModelIndex& index);

private:
  void
  setupUi(SettingsTreeModel* treeModel);

  void
  connectSignals(SettingsTreeModel* treeModel);

private:
  struct Private;

  Private* p;
};
}
}
}

#endif //  Geo_Database_SettingsWidget_hpp
