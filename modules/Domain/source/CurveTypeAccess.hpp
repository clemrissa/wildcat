#pragma once

#include <Domain/CurveType>

#include <QSharedPointer>
#include <QVector>

namespace Geo {
namespace Domain {
//

class CurveTypeAccess
{
public:
  using Shared = QSharedPointer<CurveTypeAccess>;

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

  virtual QVector<CurveType::Shared>
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
