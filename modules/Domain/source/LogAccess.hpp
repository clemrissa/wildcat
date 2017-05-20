#pragma once

#include "Log.hpp"

#include <memory>
#include <vector>

namespace Geo {
namespace Domain {
//

class LogAccess
{
public:
  using Shared = std::shared_ptr<LogAccess>;

public:
  virtual
  ~LogAccess()
  {}

  virtual void
  insert(Log::Shared log) = 0;

  virtual void
  update(Log::Shared log) = 0;

  virtual void
  remove(Log::Shared log) = 0;

  virtual void
  remove(unsigned int const& pk) = 0;

  virtual std::vector<Log::Shared>
  findAll() = 0;

  virtual Log::Shared
  findByPrimaryKey(unsigned int const& pk) = 0;
};
}
}
