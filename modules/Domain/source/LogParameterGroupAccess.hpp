#pragma once

#include <Domain/LogParameterGroup>

#include <vector>
#include <memory>

namespace Geo {
namespace Domain {
//

class LogParameterGroupAccess
{
public:
  using Shared = std::shared_ptr<LogParameterGroupAccess>;

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

  virtual std::vector<LogParameterGroup::Shared>
  findAll() = 0;

  virtual LogParameterGroup::Shared
  findByPrimaryKey(unsigned int const& pk) = 0;
};
}
}
