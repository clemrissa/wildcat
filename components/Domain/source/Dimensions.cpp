#include "Dimensions.hpp"

#include <algorithm>

using Geo::Domain::Dimensions;

Dimensions::
Dimensions()
{
  _dimensions.fill(0);

  updateFundamentalUnits();
}


Dimensions::
Dimensions(Dimension d, int const times)
{
  _dimensions[d] = times;

  updateFundamentalUnits();
}


Dimensions::
Dimensions(Dimensions const& dimensions)
{
  for (int i = 0; i < Dimension::AllUnitsSize; ++i)
    _dimensions[i] = dimensions._dimensions[i];

  updateFundamentalUnits();
}


Dimensions
Dimensions::
operator*(Dimensions const& dimensions) const
{
  Dimensions result(*this);

  for (int i = 0; i < Dimension::AllUnitsSize; ++i)
    result._dimensions[i] += dimensions._dimensions[i];

  return result;
}


Dimensions
Dimensions::
operator/(Dimensions const& dimensions) const
{
  Dimensions result(*this);

  for (int i = 0; i < Dimension::AllUnitsSize; ++i)
    result._dimensions[i] -= dimensions._dimensions[i];

  return result;
}


bool
Dimensions::
operator==(Dimensions const& dimensions) const
{
  for (int i = 0; i < Dimension::AllUnitsSize; ++i)
    if (_dimensions[i] != dimensions._dimensions[i])
      return false;

  return true;
}


/// compares just fundamental units
bool
Dimensions::
compatible(Dimensions const& dimensions) const
{
  for (int i = 0; i < Dimension::FundamentalUnitsSize; ++i)
    if (_dimensions[i] != dimensions._dimensions[i])
      return false;

  return true;
}


void
Dimensions::
updateFundamentalUnits()
{
  std::fill_n(_dimensions.begin(), FundamentalUnitsSize, 0);

  for (int i = DAngle; i < AllUnitsSize; ++i) {
    int n = _dimensions[i];

    switch (i) {
    case DAngle:
      break;

    case DSolidAngle:
      break;

    case DFrequency:
      _dimensions[DTime] -= n;
      break;

    case DForce:
      _dimensions[DMass]   += n;
      _dimensions[DLength] += n;
      _dimensions[DTime]   -= n * 2;

    case DPressure:
      _dimensions[DMass]   += n;
      _dimensions[DLength] -= n;
      _dimensions[DTime]   -= n * 2;
      break;

      // TODO: to be continued
    }
  }
}
