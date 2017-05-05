#include "Unit.hpp"

using Geo::Domain::Dimensions;
using Geo::Domain::Unit;

Unit::
Unit():
  _scale(0.0),
  _offset(0.0),
  _dimensions(Dimensions::None())
{
}


Unit::
Unit(QString const    name,
     QString const    symbol,
     double const     scale,
     double const     offset,
     Dimensions const dimensions):
  _name(name),
  _symbol(symbol),
  _scale(scale),
  _offset(offset),
  _dimensions(dimensions)
{
  //
}


double
Unit::
standardize(double value) const
{
  return _scale * value + _offset;
}


double
Unit::
destandardize(double value) const
{
  return (value - _offset) / _scale;
}


bool
Unit::
isValid() const
{
  return !_name.isEmpty() &&
         !_symbol.isEmpty() &&
         _scale != 0.0;
}
