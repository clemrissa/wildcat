#ifndef Geo_Domain_CurveTypeAccess_hpp
#define Geo_Domain_CurveTypeAccess_hpp

#include <Domain/CurveType>

#include <QSharedPointer>
#include <QVector>

namespace Geo {
namespace Domain {
//

class CurveTypeAccess
{
public:
  typedef QSharedPointer<CurveTypeAccess> Shared;

public:
  virtual
  ~CurveTypeAccess()
  {
  }

  virtual void
  insert(CurveType::Shared log) = 0;

  virtual void
  update(CurveType::Shared log) = 0;

  virtual void
  remove(CurveType::Shared log) = 0;

  virtual void
  remove(unsigned int const& pk) = 0;

  virtual QVector<CurveType::Shared>
  findAll() = 0;

  virtual CurveType::Shared
  findByPrimaryKey(unsigned int const& pk) = 0;

public:
  virtual void
  createDefaultCurveTypes() = 0;
};

//
}
}

#endif
