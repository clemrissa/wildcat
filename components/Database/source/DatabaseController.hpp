#ifndef Geo_Database_DatabaseController_hpp
#define Geo_Database_DatabaseController_hpp

#include <QObject>

namespace Geo {
namespace  Database {
class DatabaseController: public QObject {
  Q_OBJECT

public:
  static DatabaseController*
  instance();

  virtual
  ~DatabaseController();

public slots:
  void
  showSettingsWidget();

private:
  DatabaseController();

private:
  static DatabaseController* _instance;
};
}
}

#endif //  Geo_Database_DatabaseController_hpp
