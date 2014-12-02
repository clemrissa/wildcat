#ifndef Geo_Domain_Odb_UnitAccess_hpp
#define Geo_Domain_Odb_UnitAccess_hpp

#include <Domain/UnitAccess>

#include <QSharedPointer>

#include <odb/database.hxx>

namespace Geo {
namespace Domain {
namespace Odb {
//

class UnitAccess: public Geo::Domain::UnitAccess
{
public:
  typedef typename Geo::Domain::UnitAccess::Shared Shared;
  typedef QSharedPointer<odb::core::database>      Database;

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

  QVector<Unit::Shared>
  findAll();

  Geo::Domain::Unit::Shared
  findByPrimaryKey(unsigned int const& pk);

private:
  Database _db;
};

//
}
}
}

#endif //  Geo_Domain_Odb_UnitAccess_hpp
