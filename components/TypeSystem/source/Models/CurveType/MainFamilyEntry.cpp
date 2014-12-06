#include "MainFamilyEntry.hpp"

#include "FamilyEntry.hpp"

using Geo::TypeSystem::Models::CurveTypes::FamilyEntry;
using Geo::TypeSystem::Models::CurveTypes::MainFamilyEntry;

MainFamilyEntry::
MainFamilyEntry(Geo::Domain::CurveType::Shared curveType):
  TreeEntry(curveType)
{
}


MainFamilyEntry::
MainFamilyEntry(QDomElement& domElement):
  TreeEntry()
{
  _mainFamilyName = domElement.firstChildElement("MainFamily").text();

  if (_mainFamilyName.isEmpty())
    _mainFamilyName = domElement.firstChildElement("CurveMnemonic").text();
}


MainFamilyEntry::
~MainFamilyEntry()
{
}


QVariant
MainFamilyEntry::
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
MainFamilyEntry::
addChild(QDomElement& domElement)
{
  auto family = domElement.firstChildElement("Family");

  if (family.isNull())
    return;

  if (!_familyNames.contains(family.text())) {
    _familyNames.insert(family.text());
    _entries.push_back(new FamilyEntry(domElement, this));
  }
}
