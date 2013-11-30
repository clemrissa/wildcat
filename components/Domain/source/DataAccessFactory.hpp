#ifndef Geo_Domain_DataAccessFactory_hpp
#define Geo_Domain_DataAccessFactory_hpp

#include <Domain/LogAccess>

#include <QSharedPointer>

namespace Geo {
namespace Domain {
class DataAccessFactory {
public:
  typedef QSharedPointer<DataAccessFactory> Shared;

public:
  virtual
  ~DataAccessFactory() {}

  DataAccessFactory&
  operator=(DataAccessFactory const&) = delete;

  virtual LogAccess::Shared
  logAccess() const = 0;
};
}
}

#endif
