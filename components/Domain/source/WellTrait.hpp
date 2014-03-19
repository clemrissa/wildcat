#ifndef Geo_Domain_WellTrait_hpp
#define Geo_Domain_WellTrait_hpp

#include <QSharedPointer>

namespace Geo {
namespace Domain {

#ifdef ODB_COMPILER
  #pragma db object
#endif
class WellTrait {
public:
  typedef QSharedPointer<WellTrait> Shared;

  WellTrait() {}

  WellTrait(QString name);

  QString name() const { return _name; }

  void setName(QString name) { _name = name; }

private:
#ifdef ODB_COMPILER
  #pragma db id
#endif
  QString _name; 
};

}
}


#endif //  Geo_Domain_WellTrait_hpp


