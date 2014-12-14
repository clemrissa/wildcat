#include "FamilyEntry.hpp"

#include "CurveTypeEntry.hpp"

#include <QtGui/QIcon>
#include <QtGui/QPalette>

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
  switch (role) {
  case Qt::DisplayRole:
    return getDisplayOrEditRole(column);
    break;

  case Qt::EditRole:
    return getDisplayOrEditRole(column);
    break;

  case Qt::DecorationRole:
    return getDecorationRole(column);
    break;

  case Qt::ForegroundRole:
    return getForegroundRole(column);
    break;

  default:
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


QVariant
FamilyEntry::
getDisplayOrEditRole(int column) const
{
  QVariant result;

  switch (column) {
  case TreeEntry::Family:
    return _familyName;
    break;

  default:
    return QVariant();
    break;
  }
}


QVariant
FamilyEntry::
getDecorationRole(int column) const
{
  // TODO
  // if (!_unit->isValid())
  // return QVariant();

  if (column == CloseAction)

    switch (_state) {
    case Active:
      return QIcon(":/delete.png");
      break;

    case Deleted:
      return QIcon(":/revert.png");
      break;
    }

  return QVariant();
}


QVariant
FamilyEntry::
getForegroundRole(int column) const
{
  Q_UNUSED(column);

  QVariant result;

  switch (_state) {
  case Active: {
    QPalette palette;
    result =  QColor(palette.color(QPalette::WindowText));
    break;
  }

  case Deleted:
    result = QColor(Qt::lightGray);
    break;
  }

  return result;
}
