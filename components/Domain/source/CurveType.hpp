#ifndef Geo_Domain_CurveType_hpp
#define Geo_Domain_CurveType_hpp

#include <QtCore/QList>
#include <QtCore/QSharedPointer>

#include <odb/core.hxx>

namespace Geo {
namespace Domain {
//

#ifdef ODB_COMPILER
  #pragma db object
#endif
class CurveType
{
public:
  typedef QSharedPointer<CurveType> Shared;

public:
  enum Scale {
    Linear,
    Log2,
    Log10,
    ScaleSize
  };

  enum Continuity {
    Continuous,
    TopBottom,
    Blocks,
    ContinuitySize
  };

  CurveType();

public:
  // setter getters

  QString
  family() const { return _family; }
  QString
  curveType() const { return _curveType; }
  QString
  mnemonic() const { return _mnemonic; }
  QString
  unit() const { return _unit; }
  double
  min() const { return _min; }
  double
  max() const { return _max; }
  Scale
  scale() const { return _scale; }
  Continuity
  type() const { return _continuity; }
  QList<QString>
  synonyms() const { return _synonyms; }

  void
  setFamily(QString const family) { _family = family; }
  void
  setCurveType(QString const curveType)
  { _curveType = curveType; }

  void
  setMnemonic(QString const mnemonic)
  {
    _mnemonic = mnemonic;
  }

  void
  setUnit(QString const unit) { _unit = unit; }
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
  bool
  isValid() const;

private:
  friend class odb::access;

#ifdef ODB
  #pragma db id auto
#endif
  unsigned int _id;

  QString        _family;
  QString        _curveType;
  QString        _mnemonic;
  QList<QString> _synonyms;
  QString        _unit; // TODO: change to unit data type
  double         _min;
  double         _max;

  Scale      _scale;
  Continuity _continuity;
};

//
}
}
#endif //  Geo_Domain_CurveType_hpp
