#ifndef Geo_Domain_Odb_LogParameterGroupAccessObject_hpp
#define Geo_Domain_Odb_LogParameterGroupAccessObject_hpp

#include <Domain/LogParameterGroupAccess>

#include <QSharedPointer>

#include <odb/database.hxx>

namespace Geo {
namespace Domain {
namespace Odb {
class LogParameterGroupAccess: public Geo::Domain::LogParameterGroupAccess
{
public:
  typedef typename Geo::Domain::LogParameterGroupAccess::Shared Shared;
  typedef QSharedPointer<odb::core::database>                   Database;

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

  QVector<LogParameterGroup::Shared>
  findAll();

  LogParameterGroup::Shared
  findByPrimaryKey(unsigned int const& pk);

private:
  Database _db;
};
}
}
}

#endif
