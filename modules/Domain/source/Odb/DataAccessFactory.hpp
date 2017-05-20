#pragma once

#include <Domain/Odb/CurveTypeAccess>
#include <Domain/Odb/LogAccess>
#include <Domain/Odb/LogParameterAccess>
#include <Domain/Odb/LogParameterGroupAccess>
#include <Domain/Odb/UnitAccess>
#include <Domain/Odb/WellAccess>
#include <Domain/Odb/WellTraitAccess>

#include <Domain/DataAccessFactory>

#include <memory>

#include <odb/database.hxx>

namespace Geo
{
namespace Domain
{
namespace Odb
{
//

class DataAccessFactory : public Domain::DataAccessFactory
{
private:
  using Base = Geo::Domain::DataAccessFactory;

public:
  using Shared   = Base::Shared;
  using Database = std::shared_ptr<odb::core::database>;

public:
  DataAccessFactory(Database const& db) : _db(db)
  {}

  DataAccessFactory(DataAccessFactory const&) = delete;

  DataAccessFactory&
  operator=(DataAccessFactory const&) = delete;

  Database
  database() const override { return _db; }

  Domain::LogAccess::Shared
  logAccess() const override
  {
    return Domain::LogAccess::Shared(new LogAccess(_db));
  }

  Domain::WellAccess::Shared
  wellAccess() const override
  {
    return Domain::WellAccess::Shared(new WellAccess(_db));
  }

  Domain::WellTraitAccess::Shared
  wellTraitAccess() const override
  {
    return Domain::WellTraitAccess::Shared(new WellTraitAccess(_db));
  }

  Domain::LogParameterGroupAccess::Shared
  logParameterGroupAccess() const override
  {
    return Domain::LogParameterGroupAccess::Shared(
      new LogParameterGroupAccess(_db));
  }

  Domain::LogParameterAccess::Shared
  logParameterAccess() const override
  {
    return Domain::LogParameterAccess::Shared(new LogParameterAccess(_db));
  }

  Domain::UnitAccess::Shared
  unitAccess() const override
  {
    return Domain::UnitAccess::Shared(new UnitAccess(_db));
  }

  Domain::CurveTypeAccess::Shared
  curveTypeAccess() const override
  {
    return Domain::CurveTypeAccess::Shared(new CurveTypeAccess(_db));
  }

public:
  /// Performs some DB-related work after connection is established
  void
  afterDBConnected() const override
  {
    wellTraitAccess()->createDefaultTraits();

    unitAccess()->createDefaultUnits();
  }

private:
  Database _db;
};

//
}
}
}
