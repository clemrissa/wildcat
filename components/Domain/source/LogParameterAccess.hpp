#ifndef Geo_Domain_LogParameterAccess_hpp
#define Geo_Domain_LogParameterAccess_hpp

#include <Domain/LogParameter>

#include <QtCore/QSharedPointer>
#include <QtCore/QVector>

namespace Geo {
namespace Domain {
//

class LogParameterAccess
{
public:
  typedef QSharedPointer<LogParameterAccess> Shared;

public:
  virtual
  ~LogParameterAccess()
  {
  }

  virtual void
  insert(LogParameter::Shared log) = 0;

  virtual void
  update(LogParameter::Shared log) = 0;

  virtual void
  remove(LogParameter::Shared log) = 0;

  virtual void
  remove(unsigned int const& pk) = 0;

  virtual QVector<LogParameter::Shared>
  findAll() = 0;

  virtual LogParameter::Shared
  findByPrimaryKey(unsigned int const& pk) = 0;
};
}
}

#endif
