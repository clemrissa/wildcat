#ifndef Geo_Domain_WellAccessObject_hpp
#define Geo_Domain_WellAccessObject_hpp

#include <Domain/Well>

#include <QSharedPointer>
#include <QVector>

namespace Geo {
namespace Domain {
class WellAccess {
public:
  typedef QSharedPointer<WellAccess> Shared;

public:
  virtual
  ~WellAccess() {}

  virtual void
  insert(Well::Shared well) = 0;

  virtual void
  update(Well::Shared well) = 0;

  virtual void
  remove(Well::Shared well) = 0;

  virtual void
  remove(unsigned int const& uuid) = 0;

  virtual QVector<Well::Shared>
  findAll() = 0;

  virtual Well::Shared
  findByPrimaryKey(unsigned int const& pk) = 0;
};
}
}

#endif // Geo_Domain_WellAccessObject_hpp
