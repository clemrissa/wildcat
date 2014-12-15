#include "CurveTypeEntry.hpp"

#include <QtGui/QColor>
#include <QtGui/QIcon>
#include <QtGui/QPalette>

using Geo::Domain::CurveType;
using Geo::TypeSystem::Models::CurveTypes::CurveTypeEntry;
using Geo::TypeSystem::Models::CurveTypes::TreeEntry;

CurveTypeEntry::
CurveTypeEntry(Geo::Domain::CurveType::Shared curveType,
               TreeEntry*                     parent):
  TreeEntry(parent),
  _curveType(curveType),
  _persisted(_curveType->isValid())
{
}


CurveTypeEntry::
CurveTypeEntry(QDomElement& de,
               TreeEntry*   parent):
  TreeEntry(parent),
  _curveType(new CurveType()),
  _persisted(_curveType->isValid())
{
  QDomElement mnem = de.firstChildElement("CurveMnemonic");

  QString familyName;
  QString curveType;

  if (mnem.isNull()) {
    familyName = de.firstChildElement("MainFamily").text();
    curveType  = de.firstChildElement("Family").text();
  } else {
    familyName = de.firstChildElement("Family").text();
    curveType  = de.firstChildElement("SubFamily").text();
  }

  _curveType->setFamily(familyName);
  _curveType->setCurveType(curveType);

  _curveType->setMnemonic(de.firstChildElement("CurveMnemonic").text());
  _curveType->setUnit(de.firstChildElement("Unit").text());

  bool ok;
  _curveType->setMin(de.firstChildElement("Min").text().toDouble(&ok));
  _curveType->setMax(de.firstChildElement("Max").text().toDouble(&ok));

  // TODO scale
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
  // QDomElement mnem = de.firstChildElement("CurveMnemonic");

  QString mnem = de.firstChildElement("CurveMnemonic").text();

  if (_curveType->mnemonic().isEmpty())
    _curveType->setMnemonic(mnem);

  else {
    QStringList synonyms = _curveType->synonyms();

    if (!synonyms.contains(mnem)) {
      synonyms.append(mnem);

      _curveType->setSynonyms(synonyms);
    }
  }
}


QVariant
CurveTypeEntry::
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


QVariant
CurveTypeEntry::
getDisplayOrEditRole(int column) const
{
  switch (column) {
  case TreeEntry::FamilyOrCurveType:

    return _curveType->curveType();
    break;

  case TreeEntry::Mnemonic:
    return _curveType->mnemonic();
    break;

  case TreeEntry::Synonims:
    return QStringList(_curveType->synonyms()).join(",");

  case TreeEntry::Units:
    return _curveType->unit();
    break;

  case TreeEntry::Min:
    return _curveType->min();
    break;

  case TreeEntry::Max:
    return _curveType->max();
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


QVariant
CurveTypeEntry::
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
CurveTypeEntry::
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
