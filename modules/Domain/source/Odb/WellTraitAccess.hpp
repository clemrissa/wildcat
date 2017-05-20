#pragma once

#include <Domain/WellTraitAccess>

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

class WellTraitAccess : public Geo::Domain::WellTraitAccess
{
public:
  using Shared = Geo::Domain::WellTraitAccess::Shared;
  using Database = std::shared_ptr<odb::core::database>;

public:
  WellTraitAccess(Database db);

  WellTraitAccess(WellTraitAccess const&) = delete;

  WellTraitAccess&
  operator=(WellTraitAccess const&) = delete;

  void
  insert(WellTrait::Shared wellTrait) override;

  void
  update(WellTrait::Shared wellTrait) override;

  void
  remove(WellTrait::Shared wellTrait) override;

  void
  remove(unsigned int const& pk) override;

  std::vector<WellTrait::Shared>
  findAll() override;

  // findByQuery()

  WellTrait::Shared
  findByPrimaryKey(unsigned int const& pk) override;

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
