#ifndef Geo_Domain_WellTraitAccess_hpp
#define Geo_Domain_WellTraitAccess_hpp

#include <Domain/WellTrait>

#include <QSharedPointer>
#include <QVector>

namespace Geo {
namespace Domain {
//

class WellTraitAccess: public QObject
{
public:
  typedef QSharedPointer<WellTraitAccess> Shared;

public:
  virtual
  ~WellTraitAccess()
  {
  }

  virtual void
  insert(WellTrait::Shared wellTrait) = 0;

  virtual void
  update(WellTrait::Shared wellTrait) = 0;

  virtual void
  remove(WellTrait::Shared wellTrait) = 0;

  virtual void
  remove(unsigned int  const& uuid) = 0;

  virtual QVector<WellTrait::Shared>
  findAll() = 0;

  virtual WellTrait::Shared
  findByPrimaryKey(unsigned int const& pk) = 0;

public:
  virtual void
  createDefaultTraits() = 0;
};
}
}

#endif // Geo_Domain_WellTraitAccess_hpp
