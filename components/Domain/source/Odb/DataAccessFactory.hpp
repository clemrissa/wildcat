#ifndef Geo_Domain_Odb_DataAccessFactory_hpp
#define Geo_Domain_Odb_DataAccessFactory_hpp

#include <Domain/Odb/LogAccess>
#include <Domain/Odb/WellAccess>
#include <Domain/Odb/WellTraitAccess>

#include <Domain/DataAccessFactory>

#include <QSharedPointer>

#include <odb/database.hxx>

namespace Geo {
namespace Domain {
namespace Odb {
class DataAccessFactory: public Domain::DataAccessFactory {
private:
  typedef Geo::Domain::DataAccessFactory Base;

public:
  typedef typename Base::Shared               Shared;
  typedef QSharedPointer<odb::core::database> Database;

public:
  DataAccessFactory(Database const& db): _db(db) {}

  DataAccessFactory(DataAccessFactory const&) = delete;

  DataAccessFactory&
  operator=(DataAccessFactory const&) = delete;

  Database
  database() const override { return _db; }

  Domain::LogAccess::Shared
  logAccess() const override {
    return Domain::LogAccess::Shared(new LogAccess(_db));
  }

  Domain::WellAccess::Shared
  wellAccess() const override {
    return Domain::WellAccess::Shared(new WellAccess(_db));
  }

  Domain::WellTraitAccess::Shared
  wellTraitAccess() const override {
    return Domain::WellTraitAccess::Shared(new WellTraitAccess(_db));
  }

private:
  Database _db;
};
}
}
}

#endif
