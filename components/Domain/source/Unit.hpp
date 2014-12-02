#ifndef Geo_Domain_Unit_hpp
#define Geo_Domain_Unit_hpp

#include <QtCore/QSharedPointer>

#include <odb/core.hxx>

#include "Dimensions.hpp"

namespace Geo {
namespace Domain {
//

#ifdef ODB_COMPILER
  #pragma db object
#endif
class Unit
{
public:
  typedef QSharedPointer<Unit> Shared;


  Unit(QString const name, 
       QString const symbol,
       double const offset,
       double const scale,
       Dimensions const dimensions);


  /// Takes "normal" value and convers to this non-standard unit 
  /// Meter -> Foot
  /// Radian -> Degree
  double convert(double value) const;

  /// For example Celsius -> Kelvin or Inch -> Meter
  double unconvert(double value) const;

public:

  // getters
  QString getName() const { return _name;  }
  QString getSymbol() const { return _symbol; }

  double getOffset() const { return _offset; }
  double getScale() const { return _scale; }

  Dimensions getDimensions() const { return _dimensions; }

  // setters
  void setName(QString const name) { _name = name; }
  void setSymbol(QString const symbol) { _symbol = symbol; }

  void setOffset(double const offset) { _offset = offset; }
  void setScale(double const scale) { _scale = scale; }

  void setDimensions(Dimensions const & dimensions) { _dimensions = dimensions; }

private:
  friend class odb::access;

  QString _name;
  QString _symbol;

  /// For non-standard units like Celsius Degree, cm, torque in pound-foot
  double _offset;
  double _scale;

  Dimensions _dimensions;
};

//
}
}
#endif //  Geo_Domain_Unit_hpp
