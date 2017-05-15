#pragma once

#include <Domain/CurveTypeAccess>
#include <Domain/LogAccess>
#include <Domain/LogParameterAccess>
#include <Domain/LogParameterGroupAccess>
#include <Domain/UnitAccess>
#include <Domain/WellAccess>
#include <Domain/WellTraitAccess>

#include <QSharedPointer>

#include <odb/database.hxx>

namespace Geo {
namespace Domain {
/**
 * Class produces various objects for accesing ORM elements
 */
class DataAccessFactory
{
public:
  typedef QSharedPointer<DataAccessFactory> Shared;

public:
  virtual
  ~DataAccessFactory()
  {
  }

  DataAccessFactory&
  operator=(DataAccessFactory const&) = delete;

  virtual QSharedPointer<odb::core::database>
  database() const = 0;

  virtual LogAccess::Shared
  logAccess() const = 0;

  virtual WellAccess::Shared
  wellAccess() const = 0;

  virtual WellTraitAccess::Shared
  wellTraitAccess() const = 0;

  virtual LogParameterGroupAccess::Shared
  logParameterGroupAccess() const = 0;

  virtual LogParameterAccess::Shared
  logParameterAccess() const = 0;

  virtual UnitAccess::Shared
  unitAccess() const = 0;

  virtual CurveTypeAccess::Shared
  curveTypeAccess() const = 0;

public:
  virtual void
  afterDBConnected() const = 0;
};
}
}
