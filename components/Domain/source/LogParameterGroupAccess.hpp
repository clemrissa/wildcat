#ifndef Geo_Domain_LogParameterGroupAccess_hpp
#define Geo_Domain_LogParameterGroupAccess_hpp

#include <Domain/LogParameterGroup>

#include <QtCore/QSharedPointer>
#include <QtCore/QVector>

namespace Geo {
namespace Domain {
//

class LogParameterGroupAccess
{
public:
  typedef QSharedPointer<LogParameterGroupAccess> Shared;

public:
  virtual
  ~LogParameterGroupAccess()
  {
  }

  virtual void
  insert(LogParameterGroup::Shared log) = 0;

  virtual void
  update(LogParameterGroup::Shared log) = 0;

  virtual void
  remove(LogParameterGroup::Shared log) = 0;

  virtual void
  remove(unsigned int const& pk) = 0;

  virtual QVector<LogParameterGroup::Shared>
  findAll() = 0;

  virtual LogParameterGroup::Shared
  findByPrimaryKey(unsigned int const& pk) = 0;
};
}
}

#endif
