#ifndef Geo_Domain_Log_hpp
#define Geo_Domain_Log_hpp

#include <QSharedPointer>
#include <QString>
#include <QVector>

#include <odb/core.hxx>

namespace Geo {
namespace Domain {
class Well;

#ifdef ODB
  #pragma db object
#endif
class Log {
public:
  typedef QSharedPointer<Log> Shared;

  Log();

  Log(QString const& name,
      QString const& unit,
      QString const& tool);

  virtual
  ~Log();

  QString const&
  getName() const { return _name; }

  QString const&
  getUnit() const { return _unit; }

  QString const&
  getTool() const { return _tool; }

  inline
  double
  getTopDepth() const { return _topDepth; }

  inline
  double
  getBottomDepth() const {
    return _topDepth + _values.size() * _step;
  }

  inline
  double
  getStep() const { return _step; }

  int
  getCount() const { return _values.size(); }

  QVector<double> const
  getValuesVector() const { return _values; }

  void
  setName(QString const& name) { _name = name; }

  void
  setUnit(QString const& unit) { _unit = unit; }

  void
  setTool(QString const& tool) { _tool = tool; }

  // Iterator over curve values
  QVectorIterator<double>
  getValuesIterator();

private:
  friend class odb::access;

#ifdef ODB
  #pragma db id auto
#endif
  unsigned int _id;

  QString _name;
  QString _unit;
  QString _tool;

  double _topDepth;
  double _step;

  QVector<double> _values;

  void
  generateData();
};
}
}
#endif
