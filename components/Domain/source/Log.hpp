#ifndef Geo_Domain_Log_hpp
#define Geo_Domain_Log_hpp

#include <QtCore/QByteArray>
#include <QtCore/QSharedPointer>
#include <QtCore/QString>
#include <QtCore/QVector>
#include <QtCore/QWeakPointer>

#include <odb/core.hxx>

#include "CurveType.hpp"

#include "NArray.hpp"

namespace Geo {
namespace Domain {
//

class Well;

#ifdef ODB
  #pragma db object
#endif
/// Log is a function f : (x, y, ...) -> (a, b, c, ...)
/// In a common case: (depth) -> (value)
///
/// Main fields:
/// reference CurveTypes == reference Dimensions
/// data array CurveTypes == data Dimensions
/// LogParameterGroup - not null
class Log
{
public:
  typedef QSharedPointer<Log> Shared;

  Log();

  virtual
  ~Log();

  void
  setReferenceCurveTypes(std::vector<CurveType::Shared> referenceCurveTypes)
  {
    _referenceCurveTypes = referenceCurveTypes;
  }

  std::vector<Geo::Domain::CurveType::Shared>
  referenceCurveTypes() const
  {
    return _referenceCurveTypes;
  }

  void
  setDataCurveTypes(std::vector<CurveType::Shared> dataCurveTypes)
  {
    _dataCurveTypes = dataCurveTypes;
  }

  std::vector<Geo::Domain::CurveType::Shared>
  dataCurveTypes() const
  {
    return _dataCurveTypes;
  }

  void
  setDataArray(QByteArray const& dataArray)
  {
    _dataArray = dataArray;
  }

  QByteArray
  dataArray() const
  {
    return _dataArray;
  }

  void
  setWell(QSharedPointer<Well> well)
  {
    _well = well;
  }

private:
  friend class odb::access;

  unsigned int _id;

  std::vector<QSharedPointer<Geo::Domain::CurveType> > _referenceCurveTypes;

  std::vector<QSharedPointer<Geo::Domain::CurveType> > _dataCurveTypes;

  QByteArray _dataArray;

  QWeakPointer<Geo::Domain::Well> _well;

  QSharedPointer<AbstractNArray> _array;

private:
  void
  generateData();
};

//
}
}

#ifdef ODB_COMPILER
  #pragma db object(Geo::Domain::Log)
  #pragma db member(Geo::Domain::Log::_id) id auto
  #pragma db member(Geo::Domain::Log::_referenceCurveTypes)
  #pragma db member(Geo::Domain::Log::_dataCurveTypes)
  #pragma db member(Geo::Domain::Log::_well) not_null
  #pragma db member(Geo::Domain::Log::_dataArray)
  #pragma db member(Geo::Domain::Log::_array) transient

  #include "Well.hpp"
#endif

#endif
