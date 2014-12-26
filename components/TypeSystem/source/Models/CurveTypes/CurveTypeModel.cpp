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

CurveTypeModel::
CurveTypeModel()
{
  // for (LasFile::Shared lasFile : lasFiles)
  // _lasFileEntries.append(new LasFileEntry(lasFile));

  reloadCurveTypes();
}


CurveTypeModel::
~CurveTypeModel()
{
  for (TreeEntry* entry : _familyEntries)
    delete entry;
}


QVariant
CurveTypeModel::
data(const QModelIndex& index, int role) const
{
  if (!index.isValid())
    return QVariant();

  TreeEntry* entry =
    static_cast<TreeEntry*>(index.internalPointer());

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
        int                role)
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
headerData(int             section,
           Qt::Orientation orientation,
           int             role)  const
{
  QVariant result;

  if (role != Qt::DisplayRole)
    return result;

  if (orientation == Qt::Vertical)
    return result;

  switch (section) {
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

  if (!doc.setContent(&file)) {
    file.close();
    return;
  }

  file.close();

  // ------

  beginResetModel();
  {
    QDomElement docElem = doc.documentElement();

    QDomNode n = docElem.firstChild();

    while (!n.isNull()) {
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

      //

      QString familyName = family.text();

      auto familyEntry = getCachedFamilyEntry(familyName);

      familyEntry->addChild(loginfo);

      n = n.nextSibling();
    }
  }
  endResetModel();
  //
}


FamilyEntry*
CurveTypeModel::
getCachedFamilyEntry(QString familyName)
{
  FamilyEntry* result = nullptr;

  if (_familyEntryMap.contains(familyName))
    result = _familyEntryMap[familyName];

  else {
    result = new FamilyEntry(familyName);

    _familyEntryMap[familyName] = result;

    _familyEntries.append(result);
  }

  return result;
}


void
CurveTypeModel::
saveXml(QString fileName)
{
  QDomDocument doc("CurveTypes");

  QDomElement root = doc.createElement("CurveTypes");
  doc.appendChild(root);

  for (auto e : _familyEntries)
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
setConnection(Database::Connections::Connection::Shared connection)
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

  if (index.column() == TreeEntry::CloseAction
      // && index.row() != _unitEntries.size() - 1)
      ) {
    treeEntry->switchState();

    int  row = index.row();
    emit dataChanged(this->index(TreeEntry::FamilyOrCurveName, row),
                     this->index(TreeEntry::CloseAction, row));
  }
}


int
CurveTypeModel::
getEntryPosition(TreeEntry* const entry) const
{
  auto it = std::find(_familyEntries.begin(),
                      _familyEntries.end(), entry);

  return it - _familyEntries.begin();
  //
}


bool
CurveTypeModel::
setDataToCurveNode(const QModelIndex& index,
                   const QVariant&    value)
{
  if (_connection.isNull())
    return false;

  auto curveTypeEntry =
    static_cast<CurveTypeEntry*>(index.internalPointer());

  auto familyEntry =
    static_cast<FamilyEntry*>(index.parent().internalPointer());

  bool oldCurveTypeStatus = curveTypeEntry->curveType()->isValid();

  curveTypeEntry->setData(index.column(), value);

  bool newCurveTypeStatus = curveTypeEntry->curveType()->isValid();

  bool becameValid = (!oldCurveTypeStatus && newCurveTypeStatus);

  auto dataAccessFactory = _connection->dataAccessFactory();
  auto curveTypeAccess   = dataAccessFactory->curveTypeAccess();

  // not yet in the DB
  if (!curveTypeEntry->getPersisted()) {
    if (becameValid) {
      beginResetModel();
      {
        curveTypeAccess->insert(curveTypeEntry->curveType());

        curveTypeEntry->setPersisted(true);

        // we add one more empty trait
        familyEntry->addChild();
      }
      endResetModel();
    }
  } else if (newCurveTypeStatus) // it was persisted and stays valid
    curveTypeAccess->update(curveTypeEntry->curveType());

  return true;
}


bool
CurveTypeModel::
setDataToFamilyNode(const QModelIndex& index,
                    const QVariant&    value)
{
  auto familyEntry =
    static_cast<FamilyEntry*>(index.internalPointer());

  bool familyEmptyBefore = familyEntry->getFamily().isEmpty();

  { // update cache with the new familyName
    QString familyName = familyEntry->getFamily();
    _familyEntryMap.remove(familyName);

    familyEntry->setFamily(value.toString());

    _familyEntryMap[value.toString()] = familyEntry;
  }

  bool familyEmptyAfter = familyEntry->getFamily().isEmpty();

  if (familyEmptyBefore && !familyEmptyAfter) {
    int position = getEntryPosition(familyEntry);
    beginInsertRows(index, position, position + 1);
    QString emptyFamilyName;

    getCachedFamilyEntry(emptyFamilyName);

    endInsertRows();
  }

  if (index.column() != TreeEntry::FamilyOrCurveName)
    return false;

  if (_connection.isNull())
    return false;

  bool somethingWasPersisted = false;

  for (unsigned i = 0; i < familyEntry->entries().size(); ++i) {
    auto curveTypeEntry =
      static_cast<CurveTypeEntry*>(familyEntry->entries()[i]);

    bool oldCurveTypeStatus = curveTypeEntry->curveType()->isValid();

    curveTypeEntry->setData(index.column(), value);

    bool newCurveTypeStatus = curveTypeEntry->curveType()->isValid();

    bool becameValid = (!oldCurveTypeStatus && newCurveTypeStatus);

    auto dataAccessFactory = _connection->dataAccessFactory();
    auto curveTypeAccess   = dataAccessFactory->curveTypeAccess();

    // not yet in the DB
    if (!curveTypeEntry->getPersisted()) {
      if (becameValid) {
        beginResetModel();
        {
          curveTypeAccess->insert(curveTypeEntry->curveType());

          curveTypeEntry->setPersisted(true);

          somethingWasPersisted = true;

          // we add one more empty trait
          // _unitEntries.append(new UnitTableEntry());
        }
        endResetModel();
      }
    } else if (newCurveTypeStatus) { // it was persisted and stays valid
      curveTypeAccess->update(curveTypeEntry->curveType());
      somethingWasPersisted = true;
    }
  }

  return true;
}


void
CurveTypeModel::
reloadCurveTypes()
{
  if (_connection.isNull())
    return;

  beginResetModel();
  {
    qDeleteAll(_familyEntries);
    _familyEntries.resize(0);
    _familyEntryMap.clear();

    using Geo::Domain::CurveType;

    auto dataAccessFactory = _connection->dataAccessFactory();

    auto curveTypeAccess = dataAccessFactory->curveTypeAccess();

    QVector<CurveType::Shared> curveTypes = curveTypeAccess->findAll();

    for (CurveType::Shared t : curveTypes) {
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
