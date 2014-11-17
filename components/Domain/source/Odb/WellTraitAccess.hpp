#ifndef Geo_Domain_Odb_WellTraitAccessObject_hpp
#define Geo_Domain_Odb_WellTraitAccessObject_hpp

#include <Domain/WellTraitAccess>
#include <QSharedPointer>

#include <odb/database.hxx>

namespace Geo {
namespace Domain {
namespace Odb {
class WellTraitAccess: public Geo::Domain::WellTraitAccess
{
public:
  typedef typename Geo::Domain::WellTraitAccess::Shared Shared;
  typedef QSharedPointer<odb::core::database>           Database;
  typedef Geo::Domain::WellTrait                        WellTrait;

public:
  WellTraitAccess(Database db);

  WellTraitAccess(WellTraitAccess const&) = delete;

  WellTraitAccess&
  operator=(WellTraitAccess const&) = delete;

  void
  insert(WellTrait::Shared wellTrait);

  void
  update(WellTrait::Shared wellTrait);

  void
  remove(WellTrait::Shared wellTrait);

  void
  remove(QString const& pk);

  QVector<WellTrait::Shared>
  findAll();

  WellTrait::Shared
  findByPrimaryKey(QString const& pk);

public:
  void
  createDefaultTraits() override;

private:
  Database _db;
}

;
}
}
}

#endif //  Geo_Domain_Odb_WellTraitAccessObject_hpp
