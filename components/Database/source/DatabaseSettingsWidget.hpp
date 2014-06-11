#ifndef Geo_Database_DatabaseSettingsWidget_hpp
#define Geo_Database_DatabaseSettingsWidget_hpp

#include <QWidget>

namespace Geo {
namespace Database {
class DatabaseSettingsTreeModel;

class DatabaseSettingsWidget: public QWidget {
  Q_OBJECT

public:
  DatabaseSettingsWidget(DatabaseSettingsTreeModel* treeModel);

  ~DatabaseSettingsWidget();

private:
  struct Private;

  Private* p;
};
}
}

#endif //  Geo_Database_DatabaseSettingsWidget_hpp
