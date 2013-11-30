#ifndef Geo_Domain_Well_hpp
#define Geo_Domain_Well_hpp

#include "Log.hpp"

#include <QSharedPointer>
#include <QString>
#include <QUuid>
#include <QVector>

#include <odb/core.hxx>

namespace Geo {
namespace Domain {
#ifdef ODB
  #pragma db object
#endif
class Well {
public:
  typedef QSharedPointer<Well> Shared;

  Well();

  Well(
    QString const& name,
    float const&   x,
    float const&   y,
    float const&   depth,
    float const&   absDepth,
    float const&   altitude);

  Well(
    Well const& other);

  virtual
  ~Well();

  QString
  logsToString(bool isWellToString = true) const;

  QString
  toString(bool isLogToString = true) const;

  QString const&
  getName() const { return _name; }

  float const&
  getX() const { return _x;  }

  float const&
  getY() const { return _y;  }

  float const&
  getDepth() const { return _depth;  }

  float const&
  getAbsDepth() const { return _absDepth; }

  float const&
  getAltitide() const { return _altitude; }

  void
  setName(QString const& name) { _name = name; }

  void
  setX(float const& x) { _x = x; }

  void
  setY(float const& y) { _y = y; }

  void
  setDepth(float const& depth) { _depth = depth; }

  void
  setAbsDepth(float const& absDepth) { _absDepth = absDepth; }

  void
  setAltitide(float const& altitude) { _altitude = altitude; }

  void
  addLog(QSharedPointer<Log> log);

  QVectorIterator<QSharedPointer<Log> >
  getLogsListIterator();

private:
  friend class odb::access;

#ifdef ODB
  #pragma db id not_null
#endif
  QUuid _id;

  QString _name;
  float   _x;
  float   _y;
  float   _depth;
  float   _absDepth;
  float   _altitude;

  QVector<QSharedPointer<Log> > _logs;
};
}
}

#endif
