#pragma once

#include <Domain/UnitAccess>

#include <QtCore/QObject>

#include <memory>

#include <odb/database.hxx>

namespace Geo
{
namespace Domain
{
namespace Odb
{
//

class UnitAccess
  : public QObject
  , public Geo::Domain::UnitAccess
{
public:
  using Shared = Geo::Domain::UnitAccess::Shared;

  using Database = std::shared_ptr<odb::core::database>;

public:
  UnitAccess(Database db);

  UnitAccess(UnitAccess const&) = delete;

  UnitAccess&
  operator=(UnitAccess const&) = delete;

  void
  insert(Geo::Domain::Unit::Shared unit);

  void
  update(Geo::Domain::Unit::Shared unit);

  void
  remove(Geo::Domain::Unit::Shared unit);

  void
  remove(unsigned int const& pk);

  std::vector<Unit::Shared>
  findAll();

  Geo::Domain::Unit::Shared
  findByPrimaryKey(unsigned int const& pk);

public:
  void
  createDefaultUnits() override;

private:
  Database _db;
};

//
}
}
}
