#ifndef Geo_Domain_WellTraitValue_hpp
#define Geo_Domain_WellTraitValue_hpp

#include <QSharedPointer>
#include <QWeakPointer>

#include <odb/core.hxx>

namespace Geo {
namespace Domain {

  class Well;

#ifdef ODB_COMPILER
  #pragma db object polymorphic pointer(QSharedPointer)
#endif
class WellTraitAbstractValue {
public:
  typedef QSharedPointer<WellTraitAbstractValue> Shared;

public:
  virtual QString
  value() = 0;

  virtual double
  value(bool *ok) = 0;

  void 
  setWell(QSharedPointer<Well> well) {
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
  QWeakPointer<Geo::Domain::Well> _well;
};


#ifdef ODB_COMPILER
  #pragma db object
#endif
class WellTraitDoubleValue : public WellTraitAbstractValue {
public:

  virtual QString
  value() override {
    return QString::number(_value);
  }

  virtual double
  value(bool *ok) override {
    *ok = true;
    return _value;
  }

  void setValue(double value) 
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
class WellTraitStringValue : public WellTraitAbstractValue {
public:

  virtual QString
  value() override {
    return _value;
  }

  virtual double
  value(bool *ok) override {
    return _value.toDouble(ok);
  }

  void setValue(QString value)
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


#endif //  Geo_Domain_WellTraitValue_hpp
