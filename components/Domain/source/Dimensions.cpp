#include "Dimensions.hpp"

#include <algorithm>
#include <iostream>

using Geo::Domain::Dimensions;

Dimensions::
Dimensions()
{
  _dimensions.fill(0);
}


Dimensions::
Dimensions(Dimension d, int const nTimes)
{
  _dimensions.fill(0);

  _dimensions[d] = nTimes;

  if ( d >= Dimensions::FundamentalUnitsSize )
    updateFundamentalUnits();
}


Dimensions::
Dimensions(Dimensions const& dimensions)
{
  for (int i = 0; i < Dimension::AllUnitsSize; ++i)
    _dimensions[i] = dimensions._dimensions[i];
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


QString
Dimensions::
getFundamentalAsString() const
{
  QString result = QString("[%1 %2 %3 %4 %5 %6 %7 %8 %9]");

  for (int i = 0; i < Dimension::FundamentalUnitsSize; ++i)
    result = result.arg(_dimensions[i], 2);

  return result;
}


QString
Dimensions::
getDimensionName(const int d)
{
  switch (d) {
  case DLength:

    return QObject::tr("Length");
    break;

  case DMass:
    return QObject::tr("Mass");
    break;

  case DTime:
    return QObject::tr("Time");
    break;

  case  DCurrent:
    return QObject::tr("Current");
    break;

  case DTemperature:
    return QObject::tr("Temperature");
    break;

  case DLuminousIntensity:
    return QObject::tr("Luminous Intensity");
    break;

  case DAmountOfSubstance:
    return QObject::tr("Amount Of Substance");
    break;

  case DAngle:
    break;

  case DSolidAngle:
    break;

  case DFrequency:
    break;

  case DForce:
    break;

  case DPressure:
    break;

  case DEnergy:
    break;

  case DPower:
    break;

  case DCharge:
    break;

  case DVoltage:
    break;

  case DElectricCapacitance:
    break;

  case DElectricResistance:
    break;

  case DElectricalConductance:
    break;

  case DMagneticFlux:
    break;

  case DMagneticField:
    break;

  case DInductance:
    break;

  case DLuminousFlux:
    break;

  case DIlluminance:
    break;

  case DRadioactivity:
    break;

  case DAbsorbedDose:
    break;
  }

  return QString();
}


void
Dimensions::
updateFundamentalUnits()
{
  std::fill_n(_dimensions.begin(),
              FundamentalUnitsSize, 0);

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
