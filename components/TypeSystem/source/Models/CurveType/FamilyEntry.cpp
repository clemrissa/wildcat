#include "FamilyEntry.hpp"

#include "CurveTypeEntry.hpp"

using Geo::TypeSystem::Models::CurveTypes::CurveTypeEntry;
using Geo::TypeSystem::Models::CurveTypes::FamilyEntry;

FamilyEntry::
FamilyEntry(Geo::Domain::CurveType::Shared curveType):
  TreeEntry(curveType)
{
}


FamilyEntry::
FamilyEntry(QDomElement& domElement):
  TreeEntry()
{
  _mainFamilyName = domElement.firstChildElement("MainFamily").text();

  if (_mainFamilyName.isEmpty())
    _mainFamilyName = domElement.firstChildElement("CurveMnemonic").text();
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
  case TreeEntry::MainFamily:
    return _mainFamilyName;
    break;

  default:
    return QVariant();
    break;
  }

  return QVariant();
}


void
FamilyEntry::
addChild(QDomElement& domElement)
{
  auto family = domElement.firstChildElement("Family");

  if (family.isNull())
    return;

  if (!_curveNames.contains(family.text())) {
    _curveNames.insert(family.text());
    _entries.push_back(new CurveTypeEntry(domElement, this));
  }
}
