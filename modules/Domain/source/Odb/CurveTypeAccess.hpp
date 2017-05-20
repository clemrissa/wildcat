#pragma once

#include <Domain/CurveTypeAccess>

#include <memory>

#include <odb/database.hxx>

namespace Geo
{
namespace Domain
{
namespace Odb
{
//

class CurveTypeAccess : public Geo::Domain::CurveTypeAccess
{
public:

  using Shared = std::shared_ptr<Geo::Domain::CurveType>;

  using Database = std::shared_ptr<odb::core::database>;

public:
  CurveTypeAccess(Database db);

  CurveTypeAccess(CurveTypeAccess const&) = delete;

  CurveTypeAccess&
  operator=(CurveTypeAccess const&) = delete;

  void
  insert(Geo::Domain::CurveType::Shared log);

  void
  update(Geo::Domain::CurveType::Shared log);

  void
  remove(Geo::Domain::CurveType::Shared log);

  void
  remove(unsigned int const& pk);

  std::vector<CurveType::Shared>
  findAll();

  Geo::Domain::CurveType::Shared
  findByPrimaryKey(unsigned int const& pk);

public:
  void
  createDefaultCurveTypes() override;

private:
  Database _db;
};

//
}
}
}
