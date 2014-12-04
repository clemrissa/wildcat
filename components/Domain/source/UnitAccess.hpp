#ifndef Geo_Domain_UnitAccess_hpp
#define Geo_Domain_UnitAccess_hpp

#include "Unit.hpp"

#include <QSharedPointer>
#include <QVector>

namespace Geo {
namespace Domain {
//

class UnitAccess
{
public:
  typedef QSharedPointer<UnitAccess> Shared;

public:
  virtual
  ~UnitAccess()
  {
  }

  virtual void
  insert(Unit::Shared log) = 0;

  virtual void
  update(Unit::Shared log) = 0;

  virtual void
  remove(Unit::Shared log) = 0;

  virtual void
  remove(unsigned int const& pk) = 0;

  virtual QVector<Unit::Shared>
  findAll() = 0;

  virtual Unit::Shared
  findByPrimaryKey(unsigned int const& pk) = 0;

public:
  virtual void
  createDefaultUnits() = 0;
};

//
}
}

#endif
