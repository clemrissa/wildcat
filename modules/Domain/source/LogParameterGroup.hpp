#pragma once

#include "LogParameter.hpp"

#include <QtCore/QDate>

#include <memory>
#include <vector>

#include <odb/core.hxx>

namespace Geo
{
namespace Domain
{
//

class Well;

class LogParameterGroup
{
public:
  using Shared = std::shared_ptr<LogParameterGroup>;

public:
  LogParameterGroup()
  {}

  virtual
  ~LogParameterGroup()
  {}

  QDate
  getDate() { return _date; }

  void
  setDate(QDate date) { _date = date; }

  void
  setWell(std::shared_ptr<Well> well)
  {
    _well = well;
  }

private:
  friend class odb::access;

  unsigned int _id;

  std::weak_ptr<Geo::Domain::Well> _well;

  QDate _date;

  std::vector<LogParameter::Shared> _logParameters;
};
}
}

#ifdef ODB_COMPILER
  #pragma db object(Geo::Domain::LogParameterGroup) pointer (std::shared_ptr)
  #pragma db member(Geo::Domain::LogParameterGroup::_id) id auto
  #pragma db member(Geo::Domain::LogParameterGroup::_well) not_null
  #pragma db member(Geo::Domain::LogParameterGroup::_logParameters) value_not_null inverse(_logParameterGroup)

  #include "Well.hpp"
#endif
