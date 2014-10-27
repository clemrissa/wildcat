#ifndef Geo_Domain_LogParameterGroup_hpp
#define Geo_Domain_LogParameterGroup_hpp

#include "LogParameter.hpp"

#include <QtCore/QDate>
#include <QtCore/QSharedPointer>
#include <QtCore/QVector>

#include <odb/core.hxx>

namespace Geo {
namespace Domain {
//

class Well;

#ifdef ODB
  #pragma db object
#endif
class LogParameterGroup
{
public:
  typedef QSharedPointer<LogParameterGroup> Shared;

public:
  LogParameterGroup()
  {
  }

  virtual
  ~LogParameterGroup()
  {
  }

  QDate
  getDate() { return _date; }

  void
  setDate(QDate date) { _date = date; }

  void
  setWell(QSharedPointer<Well> well)
  {
    _well = well;
  }

private:
  friend class odb::access;

#ifdef ODB
  #pragma db id auto
#endif
  unsigned int _id;

#ifdef ODB_COMPILER
  #pragma db not_null
#endif
  QWeakPointer<Geo::Domain::Well> _well;

  QDate _date;

#ifdef ODB_COMPILER
  #pragma db value_not_null inverse(_logParameterGroup)
#endif
  QVector<LogParameter::Shared> _logParameters;
};
}
}

#ifdef ODB_COMPILER
  #include "Well.hpp"
#endif

#endif // Geo_Domain_LogParameterGroup_hpp
