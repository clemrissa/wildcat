#ifndef Geo_Domain_LogAccessObject_hpp
#define Geo_Domain_LogAccessObject_hpp

#include "Log.hpp"

#include <QSharedPointer>
#include <QVector>

namespace Geo {
namespace Domain {
//

class LogAccess
{
public:
  typedef QSharedPointer<LogAccess> Shared;

public:
  virtual
  ~LogAccess()
  {
  }

  virtual void
  insert(Log::Shared log) = 0;

  virtual void
  update(Log::Shared log) = 0;

  virtual void
  remove(Log::Shared log) = 0;

  virtual void
  remove(unsigned int const& pk) = 0;

  virtual QVector<Log::Shared>
  findAll() = 0;

  virtual Log::Shared
  findByPrimaryKey(unsigned int const& pk) = 0;
};
}
}

#endif
