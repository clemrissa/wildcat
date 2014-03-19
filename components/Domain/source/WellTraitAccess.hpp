#ifndef Geo_Domain_WellTraitAccessObject_hpp
#define Geo_Domain_WellTraitAccessObject_hpp

#include <Domain/WellTrait>

#include <QSharedPointer>
#include <QVector>
#include <QString>

namespace Geo {
namespace Domain {
class WellTraitAccess {
public:
  typedef QSharedPointer<WellTraitAccess> Shared;

public:
  virtual
  ~WellTraitAccess() {}

  virtual void
  insert(WellTrait::Shared wellTrait) = 0;

  virtual void
  update(WellTrait::Shared wellTrait) = 0;

  virtual void
  remove(WellTrait::Shared wellTrait) = 0;

  virtual void
  remove(QString const& uuid) = 0;

  virtual QVector<WellTrait::Shared>
  findAll() = 0;

  virtual WellTrait::Shared
  findByPrimaryKey(QString const& pk) = 0;
};
}
}

#endif // Geo_Domain_WellTraitAccessObject_hpp

