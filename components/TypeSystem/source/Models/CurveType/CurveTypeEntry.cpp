#include "CurveTypeEntry.hpp"

using Geo::TypeSystem::Models::CurveTypes::CurveTypeEntry;
using Geo::TypeSystem::Models::CurveTypes::TreeEntry;

CurveTypeEntry::
CurveTypeEntry(Geo::Domain::CurveType::Shared curveType,
               TreeEntry*                     parent):
  TreeEntry(curveType, parent)
{
}


CurveTypeEntry::
CurveTypeEntry(QDomElement& de,
               TreeEntry*   parent):
  TreeEntry(parent)
{
  QDomElement mnem = de.firstChildElement("CurveMnemonic");

  if (mnem.isNull()) {
    _familyName = de.firstChildElement("MainFamily").text();
    _curveType  = de.firstChildElement("Family").text();
  } else {
    _familyName = de.firstChildElement("Family").text();
    _curveType  = de.firstChildElement("SubFamily").text();
  }

  _mnemonic   = de.firstChildElement("CurveMnemonic").text();
  _units      = de.firstChildElement("Unit").text();
  _min        = de.firstChildElement("Min").text();
  _max        = de.firstChildElement("Max").text();
  _scale      = de.firstChildElement("Scale").text().toLower();
  _continuity = de.firstChildElement("Type").text();
}


CurveTypeEntry::
~CurveTypeEntry()
{
}


void
CurveTypeEntry::
addXmlData(QDomElement& de)
{
  QDomElement mnem = de.firstChildElement("CurveMnemonic");

  if (_mnemonic.isEmpty())
    _mnemonic = de.firstChildElement("CurveMnemonic").text();
}


QVariant
CurveTypeEntry::
data(int role, int column) const
{
  if (role != Qt::DisplayRole)
    return QVariant();

  switch (column) {
  case TreeEntry::CurveType:
    return _curveType;
    break;

  case TreeEntry::Mnemonic:
    return _mnemonic;
    break;

  case TreeEntry::Units:
    return _units;
    break;

  case TreeEntry::Min:
    return _min;
    break;

  case TreeEntry::Max:
    return _max;
    break;

  case TreeEntry::Scale:
    return _scale;
    break;

  case TreeEntry::Continuity:
    return _continuity;
    break;

  default:
    return QVariant();
    break;
  }

  return QVariant();
}
