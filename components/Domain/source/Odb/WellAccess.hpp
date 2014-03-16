#ifndef Geo_Domain_Odb_WellAccessObject_hpp
#define Geo_Domain_Odb_WellAccessObject_hpp

#include <Domain/WellAccess>
#include <QSharedPointer>

#include <odb/database.hxx>

namespace Geo {
namespace Domain {
namespace Odb {
class WellAccess: public Geo::Domain::WellAccess {
public:
  typedef typename Geo::Domain::WellAccess::Shared Shared;
  typedef QSharedPointer<odb::core::database>      Database;
  typedef Geo::Domain::Well                        Well;

public:
  WellAccess(Database db);

  WellAccess(WellAccess const&) = delete;

  WellAccess&
  operator=(WellAccess const&) = delete;

  void
  insert(Well::Shared well);

  void
  update(Well::Shared well);

  void
  remove(Well::Shared well);

  void
  remove(unsigned int const& pk);

  QVector<Well::Shared>
  findAll();

  Well::Shared
  findByPrimaryKey(unsigned int const& pk);

private:
  Database _db;
}

;
}
}
}

#endif //  Geo_Domain_Odb_WellAccessObject_hpp
