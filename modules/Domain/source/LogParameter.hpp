#pragma once

#include <QtCore/QDate>

#include <memory>

#include <odb/core.hxx>

namespace Geo
{
namespace Domain
{
//

class LogParameterGroup;

#ifdef ODB_COMPILER
  #pragma db object polymorphic pointer(std::shared_ptr)
#endif
class LogParameter
{
public:

  using Shared = std::shared_ptr<LogParameter>;

public:
  virtual
  ~LogParameter()
  {}

public:
  virtual QString
  getValue() = 0;

  virtual void
  setValue(QString value) = 0;

  void
  setLogParameterGroup(std::shared_ptr<LogParameterGroup> logParameterGroup)
  {
    _logParameterGroup = logParameterGroup;
  }

  QString
  getName()
  { return _name; }

  void
  setName(QString name)
  {
    _name = name;
  }

protected:
  friend class odb::access;

#ifdef ODB
  #pragma db id auto
#endif
  unsigned int _id;

#ifdef ODB_COMPILER
  #pragma db not_null
#endif
  std::weak_ptr<Geo::Domain::LogParameterGroup>
  _logParameterGroup;

  QString _name;
};

//-----------------------------------------------

#ifdef ODB_COMPILER
  #pragma db object
#endif
class LogParameterString : public LogParameter
{
public:
  virtual QString
  getValue() override
  {
    return _value;
  }

  void
  setValue(QString value)
  {
    _value = value;
  }

protected:
  friend class odb::access;

  QString _value;
};
}
}

#ifdef ODB_COMPILER
  #include "LogParameterGroup.hpp"
#endif
