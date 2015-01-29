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

  setDimension(d, nTimes);
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


int
Dimensions::
operator[](const int d) const
{
  return _dimensions[d];
}


void
Dimensions::
setDimension(Dimension d, int const nTimes)
{
  _dimensions[d] = nTimes;

  if (d >= Dimensions::FundamentalUnitsSize)
    updateFundamentalUnits();
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
  QString result;

  for (int i = 0; i < Dimension::FundamentalUnitsSize; ++i)
    result +=  QString("%1").arg(_dimensions[i], 2);

  return result.trimmed();
}


QString
Dimensions::
getAllUnitsAsString() const
{
  QString result;

  for (int i = 0; i < Dimension::AllUnitsSize; ++i)
    result +=  QString("%1").arg(_dimensions[i], 2);

  return result.trimmed();
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
    return QObject::tr("Angle");
    break;

  case DSolidAngle:
    return QObject::tr("Solid Angle");
    break;

  case DFrequency:
    return QObject::tr("Frequency");
    break;

  case DForce:
    return QObject::tr("Force");
    break;

  case DPressure:
    return QObject::tr("Pressure");
    break;

  case DEnergy:
    return QObject::tr("Energy");
    break;

  case DPower:
    return QObject::tr("Power");
    break;

  case DCharge:
    return QObject::tr("Charge");
    break;

  case DVoltage:
    return QObject::tr("Voltage");
    break;

  case DElectricCapacitance:
    return QObject::tr("Electric Capacitance");
    break;

  case DElectricResistance:
    return QObject::tr("Electric Resistance");
    break;

  case DElectricalConductance:
    return QObject::tr("Electric Conductance");
    break;

  case DMagneticFlux:
    return QObject::tr("Magnetic Flux");
    break;

  case DMagneticField:
    return QObject::tr("Magnetic Field");
    break;

  case DInductance:
    return QObject::tr("Inductance");
    break;

  case DLuminousFlux:
    return QObject::tr("Luminous Flux");
    break;

  case DIlluminance:
    return QObject::tr("Illuminance");
    break;

  case DRadioactivity:
    return QObject::tr("DRadioactivity");
    break;

  case DAbsorbedDose:
    return QObject::tr("Absorbed Dose");
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

    case DEnergy:
      _dimensions[DMass]   += n;
      _dimensions[DLength] += n * 2;
      _dimensions[DTime]   -= n * 2;
      break;

    case DPower:
      _dimensions[DMass]   += n;
      _dimensions[DLength] += n * 2;
      _dimensions[DTime]   -= n * 3;
      break;

    case DCharge:
      _dimensions[DTime]    += n;
      _dimensions[DCurrent] += n;
      break;

    case DVoltage:
      _dimensions[DMass]    += n;
      _dimensions[DLength]  += n * 2;
      _dimensions[DTime]    -= n * 3;
      _dimensions[DCurrent] -= n;
      break;

    case DElectricCapacitance:
      _dimensions[DMass]    -= n;
      _dimensions[DLength]  -= n * 2;
      _dimensions[DTime]    += n * 4;
      _dimensions[DCurrent] += n * 2;
      break;

    case DElectricResistance:
      _dimensions[DMass]    += n;
      _dimensions[DLength]  += n * 2;
      _dimensions[DTime]    -= n * 3;
      _dimensions[DCurrent] -= n * 2;
      break;

    case DElectricalConductance:
      _dimensions[DMass]    -= n;
      _dimensions[DLength]  -= n * 2;
      _dimensions[DTime]    += n * 3;
      _dimensions[DCurrent] += n * 2;
      break;

    case DMagneticFlux:
      _dimensions[DMass]    += n;
      _dimensions[DLength]  += n * 2;
      _dimensions[DTime]    -= n * 2;
      _dimensions[DCurrent] -= n;
      break;

    case DMagneticField:
      _dimensions[DMass]    += n;
      _dimensions[DTime]    -= n * 2;
      _dimensions[DCurrent] -= n;
      break;

    case DInductance:
      _dimensions[DMass]    += n;
      _dimensions[DLength]  += n * 2;
      _dimensions[DTime]    -= n * 2;
      _dimensions[DCurrent] -= n * 2;
      break;

    case DLuminousFlux:
      _dimensions[DLuminousIntensity] += n;
      break;

    case DIlluminance:
      _dimensions[DLength]            -= n * 2;
      _dimensions[DLuminousIntensity] += n;
      break;

    case DRadioactivity:
      _dimensions[DTime] -= n;
      break;

    case DAbsorbedDose:
      _dimensions[DLength] += n * 2;
      _dimensions[DTime]   -= n * 2;
      break;

      // TODO: to be continued
    }
  }
}
