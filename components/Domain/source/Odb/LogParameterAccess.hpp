#ifndef Geo_Domain_Odb_LogParameterAccessObject_hpp
#define Geo_Domain_Odb_LogParameterAccessObject_hpp

#include <Domain/LogParameterAccess>

#include <QSharedPointer>

#include <odb/database.hxx>

namespace Geo {
namespace Domain {
namespace Odb {
class LogParameterAccess: public Geo::Domain::LogParameterAccess
{
public:
  typedef typename Geo::Domain::LogParameterAccess::Shared Shared;
  typedef QSharedPointer<odb::core::database>              Database;

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

  QVector<LogParameter::Shared>
  findAll();

  LogParameter::Shared
  findByPrimaryKey(unsigned int const& pk);

private:
  Database _db;
};
}
}
}

#endif
