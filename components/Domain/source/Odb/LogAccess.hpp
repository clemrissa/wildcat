#ifndef Geo_Domain_Odb_LogAccessObject_hpp
#define Geo_Domain_Odb_LogAccessObject_hpp

#include <Domain/LogAccess>

#include <QSharedPointer>

#include <odb/database.hxx>

namespace Geo {
namespace Domain {
namespace Odb {
class LogAccess: public Geo::Domain::LogAccess
{
public:
  typedef typename Geo::Domain::LogAccess::Shared Shared;
  typedef QSharedPointer<odb::core::database>     Database;

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

  QVector<Log::Shared>
  findAll();

  Geo::Domain::Log::Shared
  findByPrimaryKey(unsigned int const& pk);

private:
  Database _db;
};
}
}
}

#endif
