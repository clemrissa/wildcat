#pragma once

#include <Domain/LogParameterAccess>

#include <memory>

#include <odb/database.hxx>

namespace Geo
{
namespace Domain
{
namespace Odb
{

class LogParameterAccess : public Geo::Domain::LogParameterAccess
{
public:
  using Shared   = Geo::Domain::LogParameterAccess::Shared;
  using Database = std::shared_ptr<odb::core::database>;

public:
  LogParameterAccess(Database db);

  LogParameterAccess(LogParameterAccess const&) = delete;

  LogParameterAccess&
  operator=(LogParameterAccess const&) = delete;

  void
  insert(Geo::Domain::LogParameter::Shared logParameter);

  void
  update(Geo::Domain::LogParameter::Shared logParameter);

  void
  remove(Geo::Domain::LogParameter::Shared logParameter);

  void
  remove(unsigned int const& pk);

  std::vector<LogParameter::Shared>
  findAll();

  LogParameter::Shared
  findByPrimaryKey(unsigned int const& pk);

private:
  Database _db;
};
}
}
}
