#pragma once

#include <Domain/LogAccess>

#include <memory>
#include <vector>

#include <odb/database.hxx>

namespace Geo
{
namespace Domain
{
namespace Odb
{
class LogAccess : public Geo::Domain::LogAccess
{
public:
  typedef typename Geo::Domain::LogAccess::Shared Shared;
  using Database = std::shared_ptr<odb::core::database>;

public:
  LogAccess(Database db);

  LogAccess(LogAccess const&) = delete;

  LogAccess&
  operator=(LogAccess const&) = delete;

  void
  insert(Geo::Domain::Log::Shared log);

  void
  update(Geo::Domain::Log::Shared log);

  void
  remove(Geo::Domain::Log::Shared log);

  void
  remove(unsigned int const& pk);

  std::vector<Log::Shared>
  findAll();

  Geo::Domain::Log::Shared
  findByPrimaryKey(unsigned int const& pk);

private:
  Database _db;
};
}
}
}
