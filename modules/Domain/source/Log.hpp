#pragma once

#include <QtCore/QByteArray>
#include <QtCore/QString>

#include <memory>

#include <odb/core.hxx>

#include "CurveType.hpp"
#include "NArray.hpp"

namespace Geo
{
namespace Domain
{

class LogParameterGroup;
class Well;

/// Log is a function f : (x, y, ...) -> (a, b, c, ...)
/// In a common case: (depth) -> (value);  Nx2 array
///
/// Main fields:
/// reference CurveTypes == reference Dimensions
/// data array CurveTypes == data Dimensions
/// LogParameterGroup - not null
class Log
{
public:
  using Shared = std::shared_ptr<Log>;

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
  setWell(std::shared_ptr<Well> well)
  {
    _well = well;
  }

private:
  friend class odb::access;

  unsigned int _id;

  std::vector<std::shared_ptr<Geo::Domain::CurveType> > _referenceCurveTypes;

  std::vector<std::shared_ptr<Geo::Domain::CurveType> > _dataCurveTypes;

  QByteArray _dataArray;

  std::weak_ptr<Geo::Domain::Well> _well;

  std::shared_ptr<Geo::Domain::LogParameterGroup> _logParameterGroup;

private:
  /// AbstractArray is used for accessing data stored in QByteArray
  std::shared_ptr<AbstractNArray> _array;

private:
  void
  generateData();
};

//
}
}

#ifdef ODB_COMPILER
  #pragma db object(Geo::Domain::Log) pointer (std::shared_ptr)
  #pragma db member(Geo::Domain::Log::_id) id auto
  #pragma db member(Geo::Domain::Log::_referenceCurveTypes)
  #pragma db member(Geo::Domain::Log::_dataCurveTypes)
  #pragma db member(Geo::Domain::Log::_well) not_null
  #pragma db member(Geo::Domain::Log::_dataArray)
  #pragma db member(Geo::Domain::Log::_logParameterGroup) not_null
  #pragma db member(Geo::Domain::Log::_array) transient

  #include "Well.hpp"
  #include "LogParameterGroup.hpp"
#endif
