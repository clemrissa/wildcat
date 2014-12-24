#include "CurveType.hpp"

using Geo::Domain::CurveType;

CurveType::
CurveType():
  _min(0.),
  _max(0.),
  _scale(Linear),
  _continuity(Continuity::Continuous)
{
  //
}


bool
CurveType::
isValid() const
{
  return !_family.isEmpty() &&
         !_name.isEmpty();
}
