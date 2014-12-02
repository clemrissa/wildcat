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

#ifdef ODB
  #pragma db object
#endif
class Well
{
public:
  typedef QSharedPointer<Well> Shared;

  Well();

  Well(QString const& name,
       float const&   depth,
       float const&   absDepth,
       float const&   altitude);

  Well(Well const& other);

  virtual
  ~Well();

  QString
  logsToString(bool isWellToString = true) const;

  QString
  toString(bool isLogToString = true) const;

  QString const&
  getName() const { return _name; }

  float const&
  getDepth() const { return _depth;  }

  float const&
  getAbsDepth() const { return _absDepth; }

  float const&
  getAltitide() const { return _altitude; }

  void
  setName(QString const& name) { _name = name; }

  void
  setDepth(float const& depth) { _depth = depth; }

  void
  setAbsDepth(float const& absDepth) { _absDepth = absDepth; }

  void
  setAltitide(float const& altitude) { _altitude = altitude; }

  void
  addLog(Log::Shared log);

  QVectorIterator<Log::Shared>
  getLogsListIterator();

private:
  friend class odb::access;

#ifdef ODB_COMPILER
  #pragma db id auto
#endif
  unsigned int _id;

  QString _name;
  float   _depth;
  float   _absDepth;
  float   _altitude;

#ifdef ODB_COMPILER
  #pragma db value_not_null inverse(_well)
#endif
  QVector<QSharedPointer<Log> > _logs;

  // traits
#ifdef ODB_COMPILER
  #pragma db value_not_null inverse(_well)
#endif
  QMap<QString, WellTraitAbstractValue::Shared> _traits;
};
}
}

#endif
