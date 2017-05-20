#pragma once

#include <Domain/LogParameter>

#include <vector>
#include <memory>

namespace Geo {
namespace Domain {
//

class LogParameterAccess
{
public:
  using Shared = std::shared_ptr<LogParameterAccess>;

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

  virtual std::vector<LogParameter::Shared>
  findAll() = 0;

  virtual LogParameter::Shared
  findByPrimaryKey(unsigned int const& pk) = 0;
};
}
}
