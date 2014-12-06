#include "UnitModel.hpp"

#include <QtCore/QFile>

#include "TreeEntry.hpp"

using Geo::TypeSystem::Models::Units::TreeEntry;
using Geo::TypeSystem::Models::Units::UnitModel;

UnitModel::
UnitModel()
{
  // for (LasFile::Shared lasFile : lasFiles)
  // _lasFileEntries.append(new LasFileEntry(lasFile));

  // TODO: load existing CurveTypes from database
}


UnitModel::
~UnitModel()
{
  for (TreeEntry* entry : _units)
    delete entry;
}


QVariant
UnitModel::
data(const QModelIndex& index, int role) const
{
  if (!index.isValid())
    return QVariant();

  TreeEntry* entry =
    static_cast<TreeEntry*>(index.internalPointer());

  return entry->data(role, index.column());
}


QModelIndex
UnitModel::
index(int row, int column, const QModelIndex& parent) const
{
  if (!parent.isValid())
    return QAbstractItemModel::createIndex(row, column,
                                           _units[row]);

  TreeEntry* entry =
    static_cast<TreeEntry*>(parent.internalPointer());

  if (entry->entries().size() == 0)
    return QModelIndex();

  return QAbstractItemModel::createIndex(row, column, entry->entries()[row]);
}


bool
UnitModel::
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
UnitModel::
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
UnitModel::
columnCount(const QModelIndex& parent) const
{
  Q_UNUSED(parent);
  return TreeEntry::Column::Size;
}


int
UnitModel::
rowCount(const QModelIndex& parent) const
{
  if (!parent.isValid())
    return _units.size();

  TreeEntry* entry =
    static_cast<TreeEntry*>(parent.internalPointer());

  return entry->entries().size();
}


QVariant
UnitModel::
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
  case TreeEntry::Name:
    result = tr("Name");
    break;

  case TreeEntry::Symbol:
    result = tr("Symbol");
    break;

  case TreeEntry::Offset:
    result = tr("Offset");
    break;

  case TreeEntry::Scale:
    result = tr("Scale");
    break;

  case TreeEntry::Dimensions:
    result = tr("Dimensions");
    break;

  default:
    result = QVariant();
    break;
  }

  return result;
}


Qt::ItemFlags
UnitModel::
flags(const QModelIndex& index) const
{
  Qt::ItemFlags flags = QAbstractItemModel::flags(index);

  flags |= Qt::ItemIsEditable;

  // flags ^= Qt::ItemIsSelectable;

  return flags;
}


void
UnitModel::
loadXml(QString fileName)
{
  Q_UNUSED(fileName);
}


void
UnitModel::
setConnection(Database::Connections::Connection::Shared connection)
{
  Q_UNUSED(connection);
}


int
UnitModel::
getEntryPosition(TreeEntry* const entry) const
{
  auto it = std::find(_units.begin(),
                      _units.end(), entry);

  return it - _units.begin();
  //
}
