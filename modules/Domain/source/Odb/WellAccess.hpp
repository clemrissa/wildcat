#pragma once

#include <Domain/WellAccess>

#include <memory>

#include <odb/database.hxx>

namespace Geo {
namespace Domain {
namespace Odb {
class WellAccess : public Geo::Domain::WellAccess
{
public:
  using Shared   = Geo::Domain::WellAccess::Shared;
  using Database = std::shared_ptr<odb::core::database>;
  using Well     = Geo::Domain::Well;

public:
  WellAccess(Database db);

  WellAccess(WellAccess const&) = delete;

  WellAccess&
  operator=(WellAccess const&) = delete;

  void
  insert(Well::Shared well);

  void
  update(Well::Shared well);

  void
  remove(Well::Shared well);

  void
  remove(unsigned int const& pk);

  std::vector<Well::Shared>
  findAll();

  Well::Shared
  findByPrimaryKey(unsigned int const& pk);

private:
  Database _db;
}

;
}
}
}
