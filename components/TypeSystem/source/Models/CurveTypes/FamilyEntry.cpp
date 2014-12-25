#include "FamilyEntry.hpp"

#include "CurveTypeEntry.hpp"

#include <QtCore/QAbstractItemModel>
#include <QtGui/QIcon>
#include <QtGui/QPalette>
#include <QtWidgets/QLineEdit>

using Geo::TypeSystem::Models::CurveTypes::CurveTypeEntry;
using Geo::TypeSystem::Models::CurveTypes::FamilyEntry;

FamilyEntry::
FamilyEntry(QString family):
  _family(family)
{
  QString emptyCurveName("New Curve");

  getCachedCurveTypeEntry(emptyCurveName);
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


QWidget*
FamilyEntry::
delegateWidget(int column) const
{
  QLineEdit* result = nullptr;

  if (column == TreeEntry::FamilyOrCurveName) {
    QString d = data(Qt::EditRole, column).toString();
    result = new QLineEdit(d);
  }

  return result;
}


void
FamilyEntry::
setDataFromWidget(QWidget*            editor,
                  QModelIndex const&  index,
                  QAbstractItemModel* model)
{
  if (index.column() != TreeEntry::FamilyOrCurveName)
    return;

  auto lineEdit = static_cast<QLineEdit*>(editor);
  model->setData(index, lineEdit->text(), Qt::EditRole);
}


void
FamilyEntry::
setFamily(QString family)
{
  _family = family;
}


void
FamilyEntry::
addChild(QDomElement& de)
{
  QDomElement mnem = de.firstChildElement("CurveMnemonic");

  QString curveName;

  if (mnem.isNull())
    curveName = de.firstChildElement("Family").text();
  else
    curveName = de.firstChildElement("SubFamily").text();

  auto curveTypeEntry = getCachedCurveTypeEntry(curveName);

  curveTypeEntry->addXmlData(de);
}


void
FamilyEntry::
addChild(Domain::CurveType::Shared curveType)
{
  QString curveName = curveType->name();
  _curveTypeMap.remove(curveName);

  auto curveTypeEntry = new CurveTypeEntry(curveType, this);

  _curveTypeMap[curveName] = curveTypeEntry;
  _entries.push_back(curveTypeEntry);
}


void
FamilyEntry::
addChild()
{
  QString emptyCurveName("New Curve");

  getCachedCurveTypeEntry(emptyCurveName);
}


CurveTypeEntry*
FamilyEntry::
getCachedCurveTypeEntry(QString curveTypeName)
{
  CurveTypeEntry* result = nullptr;

  if (!_curveTypeMap.contains(curveTypeName)) {
    result = new CurveTypeEntry(curveTypeName, this);

    _curveTypeMap[curveTypeName] = result;

    _entries.push_back(result);
  } else
    result = _curveTypeMap[curveTypeName];

  result->curveType()->setFamily(_family);

  return result;
}


QDomElement
FamilyEntry::
getXmlDescription(QDomDocument& doc)
{
  QDomElement tag = doc.createElement("Family");

  tag.setAttribute("Name", _family);

  for (auto e : _entries)
    tag.appendChild(e->getXmlDescription(doc));

  return tag;
}


QVariant
FamilyEntry::
getDisplayOrEditRole(int column) const
{
  QVariant result;

  switch (column) {
  case TreeEntry::FamilyOrCurveName:
    return _family;
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
