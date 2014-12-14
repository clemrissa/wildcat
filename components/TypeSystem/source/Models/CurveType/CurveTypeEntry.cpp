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
CurveTypeEntry(QDomElement& domElement,
               TreeEntry*   parent):
  TreeEntry(parent)
{
  _familyName = domElement.firstChildElement("Family").text();
  _mnemonics  = domElement.firstChildElement("Mnemonics").text();
  _units      = domElement.firstChildElement("Unit").text();
  _min        = domElement.firstChildElement("Min").text();
  _max        = domElement.firstChildElement("Max").text();
}


CurveTypeEntry::
~CurveTypeEntry()
{
}


QVariant
CurveTypeEntry::
data(int role, int column) const
{
  if (role != Qt::DisplayRole)
    return QVariant();

  switch (column) {
  case TreeEntry::CurveType:
    return _familyName;
    break;

  case TreeEntry::Mnemonics:
    return _mnemonics;
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

  default:
    return QVariant();
    break;
  }

  return QVariant();
}
