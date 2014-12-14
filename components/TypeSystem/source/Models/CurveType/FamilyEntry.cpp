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
FamilyEntry(QDomElement& de):
  TreeEntry()
{
  _familyName = de.firstChildElement("MainFamily").text();

  if (_familyName.isEmpty())
    _familyName = de.firstChildElement("Family").text();
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
  case TreeEntry::Family:
    return _familyName;
    break;

  default:
    return QVariant();
    break;
  }

  return QVariant();
}


void
FamilyEntry::
addChild(QDomElement& de)
{
  QDomElement mnem = de.firstChildElement("CurveMnemonic");

  QString curveType;

  if (mnem.isNull())
    curveType = de.firstChildElement("Family").text();
  else
    curveType = de.firstChildElement("SubFamily").text();

  if (!_curveTypes.contains(curveType)) {
    auto curveTypeEntry = new CurveTypeEntry(de, this);

    _curveTypes[curveType] = curveTypeEntry;

    _entries.push_back(curveTypeEntry);
  } else {
    auto curveTypeEntry = _curveTypes[curveType];

    curveTypeEntry->addXmlData(de);
  }
}
