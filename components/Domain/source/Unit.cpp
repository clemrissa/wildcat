#include "Units.hpp"


using Geo::Domain::Units;


Units::
Unit(QString const name, 
     QString const symbol,
     double const offset,
     double const scale,
     Dimensions const dimensions) :
  _name(name),
  _symbol(symbol),
  _offset(offset),
  _scale(scale)
  _dimensions(dimensions)
{
  //
}


double 
Units::
convert(double value) const
{
  return _scale * value + _offset;
}

double 
Units::
unconvert(double value) const
{
  return (value - _offset) / _scale;
}
