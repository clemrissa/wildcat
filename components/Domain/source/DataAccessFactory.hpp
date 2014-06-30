#ifndef Geo_Domain_DataAccessFactory_hpp
#define Geo_Domain_DataAccessFactory_hpp

#include <Domain/LogAccess>
#include <Domain/WellAccess>
#include <Domain/WellTraitAccess>

#include <QSharedPointer>

#include <odb/database.hxx>

namespace Geo {
namespace Domain {
/**
 * Class produces various objects for accesing ORM elements
 */
class DataAccessFactory {
public:
  typedef QSharedPointer<DataAccessFactory> Shared;

public:
  virtual
  ~DataAccessFactory() {}

  DataAccessFactory&
  operator=(DataAccessFactory const&) = delete;

  virtual QSharedPointer<odb::core::database> 
  database() const = 0;

  virtual LogAccess::Shared
  logAccess() const = 0;

  virtual WellAccess::Shared
  wellAccess() const = 0;

  virtual WellTraitAccess::Shared
  wellTraitAccess() const = 0;
};
}
}

#endif
