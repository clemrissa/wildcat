#ifndef Geo_Domain_Well_hpp
#define Geo_Domain_Well_hpp

#include "Log.hpp"
#include "WellTraitValue.hpp"

#include <QtCore/QMap>
#include <QtCore/QSharedPointer>
#include <QtCore/QString>
#include <QtCore/QVector>

#include <odb/core.hxx>

namespace Geo {
namespace Domain {
//

class Well
{
public:
  typedef QSharedPointer<Well> Shared;

  Well();

  Well(QString const& name);

  Well(Well const& other);

  virtual
  ~Well();

  void
  setName(QString const &name)
  { _name = name; }

  QString
  getName() const { return _name; }

  void
  addLog(Geo::Domain::Log::Shared log);

  QVectorIterator<Geo::Domain::Log::Shared>
  getLogsListIterator();

private:
  friend class odb::access;

  unsigned int _id;

  QString _name;

  QVector<QSharedPointer<Geo::Domain::Log> > _logs;

  // traits
  QMap<QString, WellTraitAbstractValue::Shared> _traits;
};
}
}

#ifdef ODB_COMPILER
  #pragma db object(Geo::Domain::Well)
  #pragma db member(Geo::Domain::Well::_id) id auto
  #pragma db member(Geo::Domain::Well::_logs) value_not_null inverse(_well)
  #pragma db member(Geo::Domain::Well::_traits) value_not_null inverse(_well)
#endif

#endif
