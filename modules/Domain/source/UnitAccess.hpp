#pragma once

#include "Unit.hpp"

#include <memory>
#include <vector>

namespace Geo
{
namespace Domain
{
//

class UnitAccess
{
public:
  using Shared = std::shared_ptr<UnitAccess>;

public:
  virtual
  ~UnitAccess()
  {}

  virtual void
  insert(Unit::Shared log) = 0;

  virtual void
  update(Unit::Shared log) = 0;

  virtual void
  remove(Unit::Shared log) = 0;

  virtual void
  remove(unsigned int const& pk) = 0;

  virtual std::vector<Unit::Shared>
  findAll() = 0;

  virtual Unit::Shared
  findByPrimaryKey(unsigned int const& pk) = 0;

public:
  virtual void
  createDefaultUnits() = 0;
};

//
}
}
