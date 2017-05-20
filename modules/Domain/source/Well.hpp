#pragma once

#include "Log.hpp"
#include "WellTraitValue.hpp"

#include <QtCore/QMap>
#include <QtCore/QString>

#include <vector>
#include <memory>

#include <odb/core.hxx>

namespace Geo
{
namespace Domain
{
//

class Well
{
public:
  using Shared = std::shared_ptr<Well>;
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

  std::vector<std::shared_ptr<Log> > &
  getLogsListIterator();

private:
  friend class odb::access;

  unsigned int _id;

  QString _name;

  std::vector<std::shared_ptr<Geo::Domain::Log> > _logs;

  // traits
  QMap<QString, WellTraitAbstractValue::Shared> _traits;
};
}
}

#ifdef ODB_COMPILER
  #pragma db object(Geo::Domain::Well) pointer (std::shared_ptr)
  #pragma db member(Geo::Domain::Well::_id) id auto
  #pragma db member(Geo::Domain::Well::_logs) value_not_null inverse(_well)
//#pragma db member(Geo::Domain::Well::_traits) value_not_null inverse(_well)
#endif
