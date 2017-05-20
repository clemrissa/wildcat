#pragma once

#include <Domain/CurveType>

#include <vector>
#include <memory>

namespace Geo {
namespace Domain {
//

class CurveTypeAccess
{
public:
  using Shared = std::shared_ptr<CurveTypeAccess>;

public:
  virtual
  ~CurveTypeAccess() = default;

  virtual void
  insert(CurveType::Shared log) = 0;

  virtual void
  update(CurveType::Shared log) = 0;

  virtual void
  remove(CurveType::Shared log) = 0;

  virtual void
  remove(unsigned int const& pk) = 0;

  virtual std::vector<CurveType::Shared>
  findAll() = 0;

  virtual CurveType::Shared
  findByPrimaryKey(unsigned int const& pk) = 0;

public:
  virtual void
  createDefaultCurveTypes() = 0;
};

//
}
}
