#include "FamilyEntry.hpp"

using Geo::TypeSystem::Models::FamilyEntry;
using Geo::TypeSystem::Models::TreeEntry;

FamilyEntry::
FamilyEntry(Geo::Domain::CurveType::Shared curveType,
            TreeEntry*                     parent):
  TreeEntry(curveType, parent)
{
}


FamilyEntry::
FamilyEntry(QDomElement& domElement,
            TreeEntry*   parent):
  TreeEntry(parent)
{
  _familyName = domElement.firstChildElement("Family").text();
}


FamilyEntry::
~FamilyEntry()
{
}


QVariant
FamilyEntry::
data(int role, int column) const
{
  if (role != Qt::DisplayRole)
    return QVariant();

  switch (column) {
  case TreeEntry::CurveType:
    return _familyName;
    break;

  default:
    return QVariant();
    break;
  }

  return QVariant();
}
