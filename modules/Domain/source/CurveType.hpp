#pragma once

#include <QtCore/QList>

#include <memory>

#include <odb/core.hxx>

#include "Unit.hpp"

namespace Geo
{
namespace Domain
{
//

#ifdef ODB_COMPILER
  #pragma db object pointer(std::shared_ptr)
#endif
class CurveType
{
public:
  using Shared = std::shared_ptr<CurveType>;

public:
  enum Scale {
    UndefinedScale,
    Linear,
    Log2,
    Log10,
    ScaleSize
  };

  enum Continuity {
    UndefinedCon,
    Continuous,
    TopBottom,
    // Blocks,
    ContinuitySize
  };

  CurveType();

public:
  // setter getters

  QString
  family() const { return _family; }

  QString
  name() const { return _name; }

  QString
  mnemonic() const { return _mnemonic; }

  QString
  textUnit() const { return _textUnit; }

  Unit::Shared
  unit() const { return _unit; }

  double
  min() const { return _min; }

  double
  max() const { return _max; }

  Scale
  scale() const { return _scale; }

  Continuity
  continuity() const { return _continuity; }

  QList<QString>
  synonyms() const { return _synonyms; }

  void
  setFamily(QString const family) { _family = family; }
  void
  setName(QString const name) { _name = name; }

  void
  setMnemonic(QString const mnemonic)
  { _mnemonic = mnemonic; }

  void
  setTextUnit(QString const textUnit) { _textUnit = textUnit; }

  void
  setUnit(Unit::Shared unit) { _unit = unit; }

  void
  setMin(double const min) { _min = min; }
  void
  setMax(double const max) { _max = max; }
  void
  setScale(Scale const scale) { _scale = scale; }
  void
  setContinuity(Continuity const continuity)
  { _continuity = continuity; }
  void
  setSynonyms(QList<QString> synonyms) { _synonyms = synonyms; }

public:
  // static functions

  static QString
  textScale(Scale s);

  static QString
  textContinuity(Continuity c);

  static Scale
  scaleFromText(QString s);

  static Continuity
  continuityFromText(QString s);

public:
  bool
  isValid() const;

private:
  friend class odb::access;

#ifdef ODB
  #pragma db id auto
#endif
  unsigned int _id;

  QString _family;
  QString _name;
  QString _mnemonic;
  QList<QString> _synonyms;
  QString _textUnit;

#ifdef ODB
  #pragma db not_null
#endif
  Unit::Shared _unit;

  double _min;
  double _max;

  Scale _scale;
  Continuity _continuity;
};

//
}
}
