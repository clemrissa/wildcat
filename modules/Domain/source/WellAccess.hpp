#pragma once

#include <Domain/Well>

#include <memory>
#include <vector>

namespace Geo {
namespace Domain {
class WellAccess
{
public:
  using Shared = std::shared_ptr<WellAccess>;

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

  virtual std::vector<Well::Shared>
  findAll() = 0;

  virtual Well::Shared
  findByPrimaryKey(unsigned int const& pk) = 0;
};
}
}
