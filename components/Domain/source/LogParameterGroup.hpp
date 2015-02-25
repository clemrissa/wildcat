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

  unsigned int _id;

  QWeakPointer<Geo::Domain::Well> _well;

  QDate _date;

  QVector<LogParameter::Shared> _logParameters;
};
}
}

#ifdef ODB_COMPILER
  #pragma db object(Geo::Domain::LogParameterGroup)
  #pragma db member(Geo::Domain::LogParameterGroup::_id) id auto
  #pragma db member(Geo::Domain::LogParameterGroup::_well) not_null
  #pragma \
  db member(Geo::Domain::LogParameterGroup::_logParameters) value_not_null inverse(_logParameterGroup)
  #include "Well.hpp"
#endif

#endif // Geo_Domain_LogParameterGroup_hpp
