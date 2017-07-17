#include "CurveTypeModel.hpp"

#include "CurveTypeEntry.hpp"
#include "FamilyEntry.hpp"

#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>
#include <QtXml/QDomText>

using Geo::TypeSystem::Models::CurveTypes::CurveTypeEntry;
using Geo::TypeSystem::Models::CurveTypes::FamilyEntry;
using Geo::TypeSystem::Models::CurveTypes::TreeEntry;

using Geo::TypeSystem::Models::CurveTypes::CurveTypeModel;

// #define DEB 1

#ifdef DEB
  #define L(a) std::cout << a << std::endl;
#else
  #define L(a)
#endif
//

CurveTypeModel::
CurveTypeModel()
{
  reloadCurveTypes();
}


CurveTypeModel::
~CurveTypeModel()
{
  deleteMarkedEntries();

  qDeleteAll(_familyEntries);
}


QVariant
CurveTypeModel::
data(const QModelIndex& index, int role) const
{
  if (!index.isValid())
    return QVariant();

  TreeEntry* entry =
    static_cast<TreeEntry*>(index.internalPointer());

  // L("take entry for data")
  // L(entry)

  return entry->data(role, index.column());
}


QModelIndex
CurveTypeModel::
index(int row, int column, const QModelIndex& parent) const
{
  if (!parent.isValid())
    return QAbstractItemModel::createIndex(row, column,
                                           _familyEntries[row]);

  TreeEntry* entry =
    static_cast<TreeEntry*>(parent.internalPointer());

  if (entry->entries().size() == 0)
    return QModelIndex();

  return QAbstractItemModel::createIndex(row, column,
                                         entry->entries()[row]);
}


bool
CurveTypeModel::
setData(const QModelIndex& index,
        const QVariant&    value,
        int role)
{
  if (role != Qt::EditRole)
    return false;

  bool result = false;

  if (index.parent().isValid())
    result = setDataToCurveNode(index, value);
  else
    result = setDataToFamilyNode(index, value);

  if (result)
    emit dataChanged(index, index);

  return result;
}


QModelIndex
CurveTypeModel::
parent(const QModelIndex& index) const
{
  TreeEntry* entry =
    static_cast<TreeEntry*>(index.internalPointer());

  Q_ASSERT(entry);

  TreeEntry* parentEntry = entry->parent();

  if (parentEntry == nullptr)
    return QModelIndex();

  TreeEntry* parentParentEntry = parentEntry->parent();

  int position = 0;

  if (parentParentEntry == nullptr)
    position = getEntryPosition(parentEntry);
  else
    position = parentParentEntry->positionOfChildEntry(parentEntry);

  return QAbstractItemModel::createIndex(position, 0, parentEntry);
}


int
CurveTypeModel::
columnCount(const QModelIndex& parent) const
{
  Q_UNUSED(parent);

  return TreeEntry::Column::Size;
}


int
CurveTypeModel::
rowCount(const QModelIndex& parent) const
{
  if (!parent.isValid())
    return _familyEntries.size();

  TreeEntry* entry =
    static_cast<TreeEntry*>(parent.internalPointer());

  return entry->entries().size();
}


QVariant
CurveTypeModel::
headerData(int section,
           Qt::Orientation orientation,
           int role)  const
{
  QVariant result;

  if (role != Qt::DisplayRole)
    return result;

  if (orientation == Qt::Vertical)
    return result;

  switch (section)
  {
    case TreeEntry::FamilyOrCurveName:
      result = tr("Family / Curve Type");
      break;

    case TreeEntry::Mnemonic:
      result = tr("Mnemonic");
      break;

    case TreeEntry::Synonyms:
      result = tr("Synonyms");
      break;

    case TreeEntry::Units:
      result = tr("Units");
      break;

    case TreeEntry::Min:
      result = tr("Min");
      break;

    case TreeEntry::Max:
      result = tr("Max");
      break;

    case TreeEntry::Scale:
      result = tr("Scale");
      break;

    case TreeEntry::Continuity:
      result = tr("Continuity");
      break;
  }

  return result;
}


Qt::ItemFlags
CurveTypeModel::
flags(const QModelIndex& index) const
{
  Qt::ItemFlags flags = QAbstractItemModel::flags(index);

  flags |= Qt::ItemIsEditable;

  // flags ^= Qt::ItemIsSelectable;

  return flags;
}


void
CurveTypeModel::
loadXml(QString fileName)
{
  QDomDocument doc("CurveTypes");

  QFile file(fileName);

  if (!file.open(QIODevice::ReadOnly))
    return;

  if (!doc.setContent(&file))
  {
    file.close();
    return;
  }

  file.close();

  // ------

  beginResetModel();
  {
    pushEmptyFamilyEntry();

    QDomElement docElem = doc.documentElement();

    QDomNode n = docElem.firstChild();

    while (!n.isNull())
    {
      CurveTypeEntry::XmlSourceType xmlCurveSourceType;

      if (n.nodeName() == QString("loginfo"))
      {
        xmlCurveSourceType = CurveTypeEntry::XmlSourceType::Schlumberger;

        // try to convert the node to an element.
        QDomElement loginfo = n.toElement();

        QDomElement mnem = loginfo.firstChildElement("CurveMnemonic");

        QDomElement family;

        // work with pair MainFamily-Family
        if (mnem.isNull())
          family = loginfo.firstChildElement("MainFamily");
        // work with Family-SubFamily
        else
          family = loginfo.firstChildElement("Family");

        if (family.isNull())
          continue;

        //

        QString familyName = family.text();

        auto familyEntry = getCachedFamilyEntry(familyName);

        familyEntry->addChild(loginfo,  xmlCurveSourceType);
      }
      else if (n.nodeName() == QString("Family"))
      {
        xmlCurveSourceType = CurveTypeEntry::XmlSourceType::Geo;
        QString familyName = n.attributes().namedItem("Name").toAttr().value();

        auto familyEntry = getCachedFamilyEntry(familyName);

        auto curve = n.firstChildElement("CurveType");

        while (!curve.isNull())
        {
          // TODO check if familyEntry became valid, save if then
          familyEntry->addChild(curve, xmlCurveSourceType);
          curve = curve.nextSiblingElement("CurveType");
        }
      }

      n = n.nextSibling();
    }

    popEmptyFamilyEntry();
  }
  endResetModel();

  // set connection to newly added nodes
  for (auto e : _familyEntries)
    e->setConnection(_connection);

  //
}


FamilyEntry*
CurveTypeModel::
getCachedFamilyEntry(QString familyName)
{
  FamilyEntry* result = nullptr;

  if (_familyEntryCacheMap.contains(familyName))
    result = _familyEntryCacheMap[familyName];

  else
  {
    result = new FamilyEntry(familyName);

    _familyEntryCacheMap[familyName] = result;

    _familyEntries.push_back(result);
  }

  return result;
}


void
CurveTypeModel::
pushEmptyFamilyEntry()
{
  if (_familyEntries.size() &&
      _familyEntries.back()->getFamily().isEmpty() &&
      _familyEntries.back()->entries().size() == 1)
  {
    auto e = _familyEntries.back()->entries().last();
    auto c = static_cast<CurveTypeEntry*>(e);

    if (c->curveType()->name().isEmpty())
    {
      Q_ASSERT(_emptyFamilyEntryStack);

      // std::cout << " PUSH " << std::endl;

      _emptyFamilyEntryStack.reset(_familyEntries.back());

      _familyEntries.erase(_familyEntries.end() - 1);
    }
  }
}


void
CurveTypeModel::
popEmptyFamilyEntry()
{
  if (_emptyFamilyEntryStack)
  {
    _familyEntries.push_back(_emptyFamilyEntryStack.release());

    // std::cout << " POP " << std::endl;
  }
}


void
CurveTypeModel::
saveXml(QString fileName)
{
  QDomDocument doc("CurveTypes");

  QDomElement root = doc.createElement("CurveTypes");

  doc.appendChild(root);

  for (auto e : _familyEntries)
    if (!e->getFamily().isEmpty())
      root.appendChild(e->getXmlDescription(doc));

  // -

  QFile file(fileName);

  if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    return;

  QTextStream out(&file);

  out << doc.toString();
}


void
CurveTypeModel::
setConnection(Database::Connection::Shared connection)
{
  _connection = connection;

  reloadCurveTypes();

  for (auto e : _familyEntries)
    e->setConnection(connection);
}


void
CurveTypeModel::
onClicked(const QModelIndex& index)
{
  auto treeEntry =
    static_cast<TreeEntry*>(index.internalPointer());

  if (index.column() == TreeEntry::CloseAction)
  {
    treeEntry->switchState();

    int row = index.row();

    emit dataChanged(this->index(row, TreeEntry::FamilyOrCurveName),
                     this->index(row, TreeEntry::CloseAction));
  }
}


int
CurveTypeModel::
getEntryPosition(TreeEntry* const entry) const
{
  auto it = std::find(_familyEntries.begin(),
                      _familyEntries.end(), entry);

  return it - _familyEntries.begin();
}


bool
CurveTypeModel::
setDataToCurveNode(const QModelIndex& index,
                   const QVariant&    value)
{
  if (!_connection)
    return false;

  auto curveTypeEntry =
    static_cast<CurveTypeEntry*>(index.internalPointer());

  auto familyEntry =
    static_cast<FamilyEntry*>(index.parent().internalPointer());

  bool oldCurveTypeStatus = curveTypeEntry->curveType()->isValid();

  if (index.column() == TreeEntry::FamilyOrCurveName)
    familyEntry->updateCachedCurveTypeEntry(curveTypeEntry,
                                            value.toString());

  curveTypeEntry->setData(index.column(), value);

  bool newCurveTypeStatus = curveTypeEntry->curveType()->isValid();

  bool becameValid = (!oldCurveTypeStatus && newCurveTypeStatus);

  auto dataAccessFactory = _connection->dataAccessFactory();
  auto curveTypeAccess   = dataAccessFactory->curveTypeAccess();

  // not yet in the DB
  if (!curveTypeEntry->getPersisted())
  {
    if (becameValid)
    {
      curveTypeAccess->insert(curveTypeEntry->curveType());

      curveTypeEntry->setPersisted(true);

      int position =
        familyEntry->positionOfChildEntry(curveTypeEntry);

      beginInsertRows(index.parent(), position, position);

      // we add one more empty trait

      familyEntry->addChild();

      endInsertRows();
    }
  }
  else if (newCurveTypeStatus)   // it was persisted and stays valid
    curveTypeAccess->update(curveTypeEntry->curveType());

  return true;
}


void
CurveTypeModel::
updateCacheWithNewFamilyName(FamilyEntry* fe, QString newFamilyName)
{   // update cache with the new familyName
  _familyEntryCacheMap.remove(fe->getFamily());
  _familyEntryCacheMap[newFamilyName] = fe;
}


bool
CurveTypeModel::
setDataToFamilyNode(const QModelIndex& index,
                    const QVariant&    value)
{
  auto familyEntry =
    static_cast<FamilyEntry*>(index.internalPointer());

  bool familyEmptyBefore = familyEntry->getFamily().isEmpty();
  {
    updateCacheWithNewFamilyName(familyEntry, value.toString());
    familyEntry->setFamily(value.toString());
  }
  bool familyEmptyAfter = familyEntry->getFamily().isEmpty();

  if (familyEmptyBefore && !familyEmptyAfter)
  {
    int position = getEntryPosition(familyEntry);
    beginInsertRows(index.parent(), position, position);
    {
      QString emptyFamilyName;

      getCachedFamilyEntry(emptyFamilyName);
    }
    endInsertRows();
  }

  if (index.column() != TreeEntry::FamilyOrCurveName)
    return false;

  if (!_connection)
    return false;

  // bool somethingWasPersisted = false;

  for (int i = 0; i < familyEntry->entries().size(); ++i)
  {
    auto curveTypeEntry =
      static_cast<CurveTypeEntry*>(familyEntry->entries()[i]);

    bool oldCurveTypeStatus = curveTypeEntry->curveType()->isValid();

    curveTypeEntry->curveType()->setFamily(value.toString());
    // curveTypeEntry->setData(index.column(), value);

    bool newCurveTypeStatus = curveTypeEntry->curveType()->isValid();

    bool becameValid = (!oldCurveTypeStatus && newCurveTypeStatus);

    auto dataAccessFactory = _connection->dataAccessFactory();
    auto curveTypeAccess   = dataAccessFactory->curveTypeAccess();

    // not yet in the DB
    if (!curveTypeEntry->getPersisted())
    {
      if (becameValid)
      {
        // beginResetModel();
        // {
        curveTypeAccess->insert(curveTypeEntry->curveType());

        curveTypeEntry->setPersisted(true);

        // somethingWasPersisted = true;

        // we add one more empty trait
        // _unitEntries.append(new UnitTableEntry());
        // }
        // endResetModel();
      }
    }
    else if (newCurveTypeStatus)   // it was persisted and stays valid
      curveTypeAccess->update(curveTypeEntry->curveType());

    // somethingWasPersisted = true;
  }

  return true;
}


void
CurveTypeModel::
reloadCurveTypes()
{
  if (!_connection)
    return;

  beginResetModel();
  {
    qDeleteAll(_familyEntries);
    _familyEntries.resize(0);
    _familyEntryCacheMap.clear();

    using Geo::Domain::CurveType;

    auto dataAccessFactory = _connection->dataAccessFactory();

    auto curveTypeAccess = dataAccessFactory->curveTypeAccess();

    std::vector<CurveType::Shared> curveTypes = curveTypeAccess->findAll();

    for (CurveType::Shared t : curveTypes)
    {
      QString familyName = t->family();

      auto familyEntry = getCachedFamilyEntry(familyName);

      familyEntry->addChild(t);
    }

    // add last empty entry
    // QString emptyFamilyName(tr("New Family"));
    QString emptyFamilyName;

    getCachedFamilyEntry(emptyFamilyName);
  }
  endResetModel();
}


void
CurveTypeModel::
deleteMarkedEntries()
{
  auto dataAccessFactory = _connection->dataAccessFactory();

  auto curveTypeAccess = dataAccessFactory->curveTypeAccess();

  for (FamilyEntry* fe : _familyEntries)

    for (TreeEntry * e : fe->entries())
    {
      auto curveTypeEntry = static_cast<CurveTypeEntry*>(e);

      if (curveTypeEntry->getPersisted() &&
          curveTypeEntry->getState() == TreeEntry::Deleted)
        curveTypeAccess->remove(curveTypeEntry->curveType());
    }
}
