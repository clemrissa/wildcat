#ifndef Geo_Domain_Dimensions_hpp
#define Geo_Domain_Dimensions_hpp

#include <QtCore/QSharedPointer>

#include <odb/core.hxx>

#include <array>

namespace Geo {
namespace Domain {
//

#ifdef ODB_COMPILER
  #pragma db value
#endif
class Dimensions
{
public:
  typedef QSharedPointer<Dimensions> Shared;

public:
  /// Every dimention tag starts with "D" to prevent
  /// name clash with static functions
  enum Dimension {
    DLength,
    DMass,
    DTime,
    DCurrent,
    DTemperature,
    DLuminousIntensity,
    DAmountOfSubstance,

    FundamentalUnitsSize,

    DAngle = FundamentalUnitsSize,
    DSolidAngle,
    DFrequency,
    DForce,
    DPressure,
    DEnergy,
    DPower,
    DCharge,
    DVoltage,
    DElectricCapacitance,
    DElectricResistance,
    DElectricalConductance,
    DMagneticFlux,
    DMagneticField,
    DInductance,
    DLuminousFlux,
    DIlluminance,
    DRadioactivity,
    DAbsorbedDose,

    AllUnitsSize
  };

public:
  /// Creates non-dimensional value
  Dimensions();

  /// Sets d-th dimension to times
  Dimensions(Dimension d, int const times = 1);

  Dimensions(Dimensions const& dimensions);

  Dimensions
  operator*(Dimensions const& dimensions) const;

  Dimensions
  operator/(Dimensions const& dimensions) const;

  /// full equality, compares all dimensions
  bool
  operator==(Dimensions const& dimensions) const;

  /// compares just fundamental units
  bool
  compatible(Dimensions const& dimensions) const;

public:
  QString
  getFundamentalAsString() const;

public:
  static Dimensions
  None() { return Dimensions(); }

  static Dimensions
  Length() { return Dimensions(DLength, 1); }

  static Dimensions
  Mass() { return Dimensions(DMass, 1); }

  static Dimensions
  Time() { return Dimensions(DTime, 1); }

  static Dimensions
  Current() { return Dimensions(DCurrent, 1); }

  static Dimensions
  Temperature() { return Dimensions(DTemperature, 1); }

  static Dimensions
  LuminousIntensity() { return Dimensions(DLuminousIntensity, 1); }

  static Dimensions
  AmountOfSubstance() { return Dimensions(DAmountOfSubstance, 1); }

  static Dimensions
  Angle() { return Dimensions(DLength, 1) * Dimensions(DLength, -1); }

  static Dimensions
  SolidAngle() { return Dimensions(DLength, 2) * Dimensions(DLength, -2); }

  // constexpr static Dimensions
  // Len() const { return Dimensions(Length, 1); }

private:
  // TODO: finish
  void
  updateFundamentalUnits();

private:
  friend class odb::access;

  std::array<int, AllUnitsSize> _dimensions;
};

//
}
}
#endif //  Geo_Domain_Dimensions_hpp
