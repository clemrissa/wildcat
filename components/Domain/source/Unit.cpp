#include "Unit.hpp"

using Geo::Domain::Dimensions;
using Geo::Domain::Unit;

Unit::
Unit(QString const    name,
     QString const    symbol,
     double const     offset,
     double const     scale,
     Dimensions const dimensions):
  _name(name),
  _symbol(symbol),
  _offset(offset),
  _scale(scale),
  _dimensions(dimensions)
{
  //
}


double
Unit::
convert(double value) const
{
  return _scale * value + _offset;
}


double
Unit::
unconvert(double value) const
{
  return (value - _offset) / _scale;
}
