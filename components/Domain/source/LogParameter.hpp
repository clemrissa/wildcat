#ifndef Geo_Domain_LogParameter_hpp
#define Geo_Domain_LogParameter_hpp

#include <QtCore/QDate>
#include <QtCore/QSharedPointer>

#include <odb/core.hxx>

namespace Geo {
namespace Domain {
//

class LogParameterGroup;

#ifdef ODB_COMPILER
  #pragma db object polymorphic pointer(QSharedPointer)
#endif
class LogParameter
{
public:
  typedef QSharedPointer<LogParameter> Shared;

public:
  virtual
  ~LogParameter()
  {
  }

public:
  virtual QString
  getValue() = 0;

  virtual void
  setValue(QString value) = 0;

  void
  setLogParameterGroup(QSharedPointer<LogParameterGroup> logParameterGroup)
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
  QWeakPointer<Geo::Domain::LogParameterGroup>
  _logParameterGroup;

  QString _name;
};


//-----------------------------------------------


#ifdef ODB_COMPILER
  #pragma db object
#endif
class LogParameterString: public LogParameter
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

#endif // Geo_Domain_LogParameter_hpp
