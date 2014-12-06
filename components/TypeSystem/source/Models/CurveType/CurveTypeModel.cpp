#include "CurveTypeModel.hpp"

#include "MainFamilyEntry.hpp"

#include <QtCore/QFile>

using Geo::TypeSystem::Models::CurveTypes::MainFamilyEntry;
using Geo::TypeSystem::Models::CurveTypes::TreeEntry;

using Geo::TypeSystem::Models::CurveTypes::CurveTypeModel;

CurveTypeModel::
CurveTypeModel()
{
  // for (LasFile::Shared lasFile : lasFiles)
  // _lasFileEntries.append(new LasFileEntry(lasFile));

  // TODO: load existing CurveTypes from database
}


CurveTypeModel::
~CurveTypeModel()
{
  for (TreeEntry* entry : _curveTypeEntries)
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
                                           _curveTypeEntries[row]);

  TreeEntry* entry =
    static_cast<TreeEntry*>(parent.internalPointer());

  if (entry->entries().size() == 0)
    return QModelIndex();

  return QAbstractItemModel::createIndex(row, column, entry->entries()[row]);
}


bool
CurveTypeModel::
setData(const QModelIndex& index,
        const QVariant&    value,
        int                role)
{
  if (role != Qt::EditRole)
    return false;

  auto treeEntry =
    static_cast<TreeEntry*>(index.internalPointer());

  bool result = treeEntry->setData(role, index.column(), value);

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
  return TreeEntry::Column::Size;
}


int
CurveTypeModel::
rowCount(const QModelIndex& parent) const
{
  if (!parent.isValid())
    return _curveTypeEntries.size();

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
  case TreeEntry::MainFamily:
    result = tr("Main Family");
    break;

  case TreeEntry::CurveType:
    result = tr("Curve Type");
    break;

  case TreeEntry::Mnemonics:
    result = tr("Mnemonics");
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

    QMap<QString, MainFamilyEntry*> mainFamilyEntryMap;

    while (!n.isNull()) {
      // try to convert the node to an element.
      QDomElement loginfo = n.toElement();

      QDomElement e = loginfo.firstChildElement("MainFamily");

      if (e.isNull())
        e = loginfo.firstChildElement("CurveMnemonic");

      QString mainFamilyName = e.text();

      MainFamilyEntry* mainFamilyEntry = nullptr;

      if (mainFamilyEntryMap.contains(mainFamilyName))
        mainFamilyEntry = mainFamilyEntryMap[mainFamilyName];
      else {
        mainFamilyEntry = new MainFamilyEntry(loginfo);

        mainFamilyEntryMap[mainFamilyName] = mainFamilyEntry;

        _curveTypeEntries.append(mainFamilyEntry);
      }

      mainFamilyEntry->addChild(loginfo);

      n = n.nextSibling();
    }
  }
  endResetModel();
  //
}


void
CurveTypeModel::
setConnection(Database::Connections::Connection::Shared connection)
{
  Q_UNUSED(connection);
}


int
CurveTypeModel::
getEntryPosition(TreeEntry* const entry) const
{
  auto it = std::find(_curveTypeEntries.begin(),
                      _curveTypeEntries.end(), entry);

  return it - _curveTypeEntries.begin();
  //
}