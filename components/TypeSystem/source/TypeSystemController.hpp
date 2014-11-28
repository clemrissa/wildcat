#ifndef Geo_TypeSystem_TypeSystemController_hpp
#define Geo_TypeSystem_TypeSystemController_hpp

#include <QObject>

namespace Geo {
namespace  TypeSystem {
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
  showCurveTypeWidget();

private:
  TypeSystemController();

private:
  static TypeSystemController* _instance;
};
}
}

#endif //  Geo_TypeSystem_TypeSystemController_hpp
