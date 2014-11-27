#ifndef Geo_Database_TypeSystemController_hpp
#define Geo_Database_TypeSystemController_hpp

#include <QObject>

namespace Geo {
namespace  Database {
class TypeSystemController: public QObject
{
  Q_OBJECT

public:
  static TypeSystemController*
  instance();

  virtual
  ~TypeSystemController();

public slots:
  void
  showConnectionsWidget();

  void
  showSettingsWidget();

private:
  TypeSystemController();

private:
  static TypeSystemController* _instance;
};
}
}

#endif //  Geo_Database_TypeSystemController_hpp
