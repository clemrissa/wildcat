#ifndef Geo_Domain_Odb_CurveTypeAccess_hpp
#define Geo_Domain_Odb_CurveTypeAccess_hpp

#include <Domain/CurveTypeAccess>

#include <QSharedPointer>

#include <odb/database.hxx>

namespace Geo {
namespace Domain {
namespace Odb {
//

class CurveTypeAccess: public Geo::Domain::CurveTypeAccess
{
public:
  typedef QSharedPointer<Geo::Domain::CurveType> Shared;
  typedef QSharedPointer<odb::core::database>    Database;

public:
  CurveTypeAccess(Database db);

  CurveTypeAccess(CurveTypeAccess const&) = delete;

  CurveTypeAccess&
  operator=(CurveTypeAccess const&) = delete;

  void
  insert(Geo::Domain::CurveType::Shared log);

  void
  update(Geo::Domain::CurveType::Shared log);

  void
  remove(Geo::Domain::CurveType::Shared log);

  void
  remove(unsigned int const& pk);

  QVector<CurveType::Shared>
  findAll();

  Geo::Domain::CurveType::Shared
  findByPrimaryKey(unsigned int const& pk);

private:
  Database _db;
};
}
}
}

#endif
