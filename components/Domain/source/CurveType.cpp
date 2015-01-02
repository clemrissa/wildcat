#include "CurveType.hpp"

#include <QtCore/QObject>

using Geo::Domain::CurveType;

CurveType::
CurveType():
  _min(0.),
  _max(0.),
  _scale(Linear),
  _continuity(Continuous)
{
  //
}


QString
CurveType::
textScale(Scale s)
{
  QString result;

  switch (s) {
  case UndefinedScale:
    break;

  case Linear:
    result = QObject::tr("Linear");
    break;

  case Log2:
    result = QObject::tr("Log2");
    break;

  case Log10:
    result = QObject::tr("Log2");

    break;

  default:
    break;
  }

  return result;
}


QString
CurveType::
textContinuity(Continuity c)
{
  QString result;

  switch (c) {
  case UndefinedCon:
    break;

  case Continuous:
    result = QObject::tr("Continuous");
    break;

  case TopBottom:
    result = QObject::tr("TopBottom");
    break;

  default:
    break;
  }

  return result;
}


bool
CurveType::
isValid() const
{
  return !_family.isEmpty() &&
         !_name.isEmpty() &&
         !_mnemonic.isEmpty() &&
         !_unit.isNull() &&
         _scale != UndefinedScale &&
         _continuity != UndefinedCon;
}
