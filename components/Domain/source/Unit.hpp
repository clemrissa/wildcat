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

  // template <typename... Ts>
  // static Shared
  // create(Ts... args)
  // {
  // return Shared(new Unit(args...));
  // }

  static Shared
  create(QString const    name,
         QString const    symbol,
         double const     scale,
         double const     offset,
         Dimensions const dimensions)
  {
    return Shared(new Unit(name,
                           symbol,
                           scale,
                           offset,
                           dimensions));
  }

public:
  Unit();

  Unit(QString const    name,
       QString const    symbol,
       double const     scale,
       double const     offset,
       Dimensions const dimensions);

  virtual
  ~Unit()
  {
  }

  /// For example: Celsius -> Kelvin
  ///              Inch -> Meter
  ///              Lbm -> Kg
  double
  standardize(double value) const;

  /// Takes "normal" value and convers to this non-standard unit
  /// Meter -> Foot
  /// Radian -> Degree
  double
  destandardize(double value) const;

  bool
  isValid() const;

public:
  // getters
  QString
  getName() const { return _name;  }
  QString
  getSymbol() const { return _symbol; }

  double
  getOffset() const { return _offset; }
  double
  getScale() const { return _scale; }

  Dimensions const&
  getDimensions() const { return _dimensions; }

  Dimensions&
  getDimensions() { return _dimensions; }

  // setters
  void
  setName(QString const name) { _name = name; }
  void
  setSymbol(QString const symbol) { _symbol = symbol; }

  void
  setOffset(double const offset) { _offset = offset; }
  void
  setScale(double const scale) { _scale = scale; }

  void
  setDimensions(Dimensions const& dimensions) { _dimensions = dimensions; }

private:
  friend class odb::access;

#ifdef ODB_COMPILER
  #pragma db id auto
#endif
  unsigned int _id;

  QString _name;
  QString _symbol;

  /// For non-standard units like Celsius Degree,
  /// cm, torque in pound-foot.
  /// Standard units (SI) have 1.0 and 1.0
  double _scale;
  double _offset;

  Dimensions _dimensions;
};

//
}
}
#endif //  Geo_Domain_Unit_hpp
