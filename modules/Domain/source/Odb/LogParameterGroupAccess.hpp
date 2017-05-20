#pragma once

#include <Domain/LogParameterGroupAccess>

#include <memory>

#include <odb/database.hxx>

namespace Geo
{
namespace Domain
{
namespace Odb
{

class LogParameterGroupAccess : public Geo::Domain::LogParameterGroupAccess
{
public:

  using Shared   = Geo::Domain::LogParameterGroupAccess::Shared;
  using Database = std::shared_ptr<odb::core::database>;

public:
  LogParameterGroupAccess(Database db);

  LogParameterGroupAccess(LogParameterGroupAccess const&) = delete;

  LogParameterGroupAccess&
  operator=(LogParameterGroupAccess const&) = delete;

  void
  insert(Geo::Domain::LogParameterGroup::Shared log);

  void
  update(Geo::Domain::LogParameterGroup::Shared log);

  void
  remove(Geo::Domain::LogParameterGroup::Shared log);

  void
  remove(unsigned int const& pk);

  std::vector<LogParameterGroup::Shared>
  findAll();

  LogParameterGroup::Shared
  findByPrimaryKey(unsigned int const& pk);

private:
  Database _db;
};
}
}
}
