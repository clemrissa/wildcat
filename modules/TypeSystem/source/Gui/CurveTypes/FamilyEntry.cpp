#include "FamilyEntry.hpp"

// #include "CurveTypeEntry.hpp"

#include <QtCore/QAbstractItemModel>
#include <QtGui/QIcon>
#include <QtGui/QPalette>
#include <QtWidgets/QLineEdit>

using Geo::TypeSystem::Gui::CurveTypes::CurveTypeEntry;
using Geo::TypeSystem::Gui::CurveTypes::FamilyEntry;

FamilyEntry::
FamilyEntry(QString family)
  : TreeEntry()
  , _family(family)
{
  addChild();
}


FamilyEntry::
~FamilyEntry()
{}

QVariant
FamilyEntry::
data(int role, int column) const
{
  switch (role)
  {
    case Qt::DisplayRole:
      return getDisplayRole(column);
      break;

    case Qt::EditRole:
      return getEditRole(column);
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

  if (column == TreeEntry::FamilyOrCurveName)
  {
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
addChild(QDomElement& de, CurveTypeEntry::XmlSourceType type)
{
  QString curveName;

  switch (type)
  {
    case CurveTypeEntry::XmlSourceType::Schlumberger:
    {
      QDomElement mnem = de.firstChildElement("CurveMnemonic");

      if (mnem.isNull())
        curveName = de.firstChildElement("Family").text();
      else
        curveName = de.firstChildElement("SubFamily").text();

      break;
    }

    case CurveTypeEntry::XmlSourceType::Geo:
    {
      curveName = de.firstChildElement("Name").text();

      break;
    }
  }

  pushInvalidCurveTypeEntry();
  {
    auto curveTypeEntry = getCachedCurveTypeEntry(curveName);

    curveTypeEntry->addXmlData(de, type);
  }
  popInvalidCurveTypeEntry();
}


// TODO: ask from cache and put there shared pointer?
void
FamilyEntry::
addChild(Domain::CurveType::Shared curveType)
{
  pushInvalidCurveTypeEntry();
  {
    QString curveName = curveType->name();
    _curveTypeMap.remove(curveName);

    auto curveTypeEntry = new CurveTypeEntry(curveType, this);

    _curveTypeMap[curveName] = curveTypeEntry;
    _entries.append(curveTypeEntry);
  }
  popInvalidCurveTypeEntry();
}


void
FamilyEntry::
addChild()
{
  QString emptyCurveName;

  getCachedCurveTypeEntry(emptyCurveName);
}


CurveTypeEntry*
FamilyEntry::
getCachedCurveTypeEntry(QString curveTypeName)
{
  CurveTypeEntry* result = nullptr;

  if (!_curveTypeMap.contains(curveTypeName))
  {
    result = new CurveTypeEntry(curveTypeName, this);

    _curveTypeMap[curveTypeName] = result;

    _entries.push_back(result);
  }
  else
    result = _curveTypeMap[curveTypeName];

  result->curveType()->setFamily(_family);

  return result;
}


void
FamilyEntry::
updateCachedCurveTypeEntry(CurveTypeEntry* curveTypeEntry,
                           QString newName)
{
  auto oldName = curveTypeEntry->curveType()->name();

  _curveTypeMap.remove(oldName);

  _curveTypeMap[newName] = curveTypeEntry;
}


QDomElement
FamilyEntry::
getXmlDescription(QDomDocument& doc)
{
  QDomElement tag = doc.createElement("Family");

  tag.setAttribute("Name", _family);

  for (auto e : _entries)
  {
    auto ct = static_cast<CurveTypeEntry*>(e);

    if (ct->curveType()->isValid())
      tag.appendChild(e->getXmlDescription(doc));
  }

  return tag;
}


QVariant
FamilyEntry::
getDisplayRole(int column) const
{
  QVariant result;

  switch (column)
  {
    case TreeEntry::FamilyOrCurveName:

      if (_family.isEmpty())
        return tr("Change family name");
      else
        return _family;

      break;

    default:
      return QVariant();
      break;
  }
}


QVariant
FamilyEntry::
getEditRole(int column) const
{
  QVariant result;

  switch (column)
  {
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

    switch (_state)
    {
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

  switch (_state)
  {
    case Active:
    {
      QPalette palette;
      result = QColor(palette.color(QPalette::WindowText));
      break;
    }

    case Deleted:
      result = QColor(Qt::lightGray);
      break;
  }

  if (column == TreeEntry::FamilyOrCurveName)
    if (_family.isEmpty())
      result = QColor(Qt::lightGray);

  return result;
}


void
FamilyEntry::
pushInvalidCurveTypeEntry()
{
  //
  if (_entries.size())
  {
    auto e = static_cast<CurveTypeEntry*>(_entries.last());

    if (!e->curveType()->isValid())
    {
      Q_ASSERT(_invalidCurveTypeEntryStack.isNull());

      // std::cout << "\t PUSH " << std::endl;

      _invalidCurveTypeEntryStack =
        static_cast<CurveTypeEntry*>(_entries.takeLast());
    }
  }
}


void
FamilyEntry::
popInvalidCurveTypeEntry()
{
  if (!_invalidCurveTypeEntryStack.isNull())
  {
    _entries.append(_invalidCurveTypeEntryStack.data());
    _invalidCurveTypeEntryStack.clear();
    // std::cout << "\t POP " << std::endl;
  }
}
