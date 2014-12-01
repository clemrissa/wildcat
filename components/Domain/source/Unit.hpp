#ifndef Geo_Domain_Unit_hpp
#define Geo_Domain_Unit_hpp

#include <QtCore/QSharedPointer>

#include <odb/core.hxx>

#include "Dimensions.hpp"

namespace Geo {
namespace Domain {
//

#ifdef ODB_COMPILER
  #pragma db object
#endif
class Unit
{
public:
  typedef QSharedPointer<Unit> Shared;

private:
  friend class odb::access;

  Dimensions _dimensions;
};

//
}
}
#endif //  Geo_Domain_Unit_hpp
