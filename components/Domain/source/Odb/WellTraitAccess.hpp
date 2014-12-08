#ifndef Geo_Domain_Odb_WellTraitAccessObject_hpp
#define Geo_Domain_Odb_WellTraitAccessObject_hpp

#include <Domain/WellTraitAccess>
#include <QSharedPointer>

#include <odb/database.hxx>
#include <odb/query.hxx>

// TODO fix
// typedef odb::query<Geo::Domain::WellTrait>  ___Query;
// typedef odb::result<Geo::Domain::WellTrait> Result;

namespace Geo {
namespace Domain {
//

namespace Odb {
//

class WellTraitAccess: public Geo::Domain::WellTraitAccess
{
public:
  typedef typename Geo::Domain::WellTraitAccess::Shared Shared;
  typedef QSharedPointer<odb::core::database>           Database;
  // typedef Geo::Domain::WellTrait                        WellTrait;

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
  remove(unsigned int const& pk);

  QVector<WellTrait::Shared>
  findAll();

  // findByQuery()

  WellTrait::Shared
  findByPrimaryKey(unsigned int const& pk);

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
