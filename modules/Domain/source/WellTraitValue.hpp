#pragma once

#include <memory>

#include <QtCore/QString>

#include <odb/core.hxx>

namespace Geo
{
namespace Domain
{
//

class Well;

#ifdef ODB_COMPILER
  #pragma db object polymorphic pointer(std::shared_ptr)
#endif
class WellTraitAbstractValue
{
public:
  typedef std::shared_ptr<WellTraitAbstractValue> Shared;

public:
  virtual QString
  value() = 0;

  virtual double
  value(bool* ok) = 0;

  void
  setWell(std::shared_ptr<Well> well)
  {
    _well = well;
  }

protected:
  friend class odb::access;

#ifdef ODB_COMPILER
  #pragma db id auto
#endif
  unsigned long _id;

#ifdef ODB_COMPILER
  #pragma db not_null
#endif
  std::weak_ptr<Geo::Domain::Well> _well;
};

#ifdef ODB_COMPILER
  #pragma db object
#endif
class WellTraitDoubleValue : public WellTraitAbstractValue
{
public:
  virtual QString
  value() override
  {
    return QString::number(_value);
  }

  virtual double
  value(bool* ok) override
  {
    *ok = true;
    return _value;
  }

  void
  setValue(double value)
  {
    _value = value;
  }

protected:
  friend class odb::access;

  double _value;
};

#ifdef ODB_COMPILER
  #pragma db object
#endif
class WellTraitStringValue : public WellTraitAbstractValue
{
public:
  virtual QString
  value() override
  {
    return _value;
  }

  virtual double
  value(bool* ok) override
  {
    return _value.toDouble(ok);
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
  #include "Well.hpp"
#endif
