#include "ImportTreeModel.hpp"

#include "Las/LasFile.hpp"
#include "Las/TreeWrapper/LasFileEntry.hpp"
#include "Las/TreeWrapper/TreeEntry.hpp"

#include <QSharedPointer>

#include <algorithm>

using Geo::Import::ImportTreeModel;
using Geo::Import::TreeWrapper::LasFileEntry;
using Geo::Import::TreeWrapper::TreeEntry;

ImportTreeModel::
ImportTreeModel(std::vector<std::shared_ptr<LasFile> > lasFiles)
{
  for (std::shared_ptr<LasFile> lasFile : lasFiles)
    _lasFileEntries.push_back(std::make_unique<LasFileEntry>(lasFile));
}


ImportTreeModel::
~ImportTreeModel()
{
}


// -------------------------------------------

//std::vector<std::unique_ptr<LasFileEntry>> const &
std::vector<std::unique_ptr<TreeEntry>> const &
ImportTreeModel::
getLasFileEntries() const
{
  return _lasFileEntries;
}


void
ImportTreeModel::
setConnection(std::shared_ptr<IConnection> connection)
{
  beginResetModel();

  _connection = connection;

  for (std::unique_ptr<TreeWrapper::TreeEntry> & e : _lasFileEntries)
    e->setConnection(connection);

  endResetModel();
}


// --------------------------------------------

QVariant
ImportTreeModel::
data(const QModelIndex& index, int role) const
{
  if (!index.isValid())
    return QVariant();

  TreeEntry* entry =
    static_cast<TreeEntry*>(index.internalPointer());

  return entry->data(role, index.column());
}


bool
ImportTreeModel::
setData(const QModelIndex& index,
        const QVariant&    value,
        int role)
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
ImportTreeModel::
index(int row, int column, const QModelIndex& parent) const
{
  if (!parent.isValid())
    return QAbstractItemModel::createIndex(row, column, _lasFileEntries[row].get());

  TreeEntry* entry =
    static_cast<TreeEntry*>(parent.internalPointer());

  if (entry->entries().size() == 0)
    return QModelIndex();

  return QAbstractItemModel::createIndex(row, column, entry->entries()[row].get());
}


QModelIndex
ImportTreeModel::
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
ImportTreeModel::
columnCount(const QModelIndex& parent) const
{
  return TreeEntry::Column::Size;
}


int
ImportTreeModel::
rowCount(const QModelIndex& parent) const
{
  if (!parent.isValid())
    return _lasFileEntries.size();

  TreeEntry* entry =
    static_cast<TreeEntry*>(parent.internalPointer());

  return entry->entries().size();
}


QVariant
ImportTreeModel::
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
    case TreeEntry::Name:
      result = tr("Item");
      break;

    case TreeEntry::Description:
      result = tr("Description");
      break;

    case TreeEntry::Value:
      result = tr("Parsed Value");
      break;

    case TreeEntry::ImportValue:
      result = tr("Import Value");
      break;

    case TreeEntry::Type:
      result = tr("Trait/Type");
      break;

    case TreeEntry::Units:
      result = tr("Parsed Units");
      break;

    case TreeEntry::ImportUnits:
      result = tr("Import Units As");
      break;
  }

  return result;
}


Qt::ItemFlags
ImportTreeModel::
flags(const QModelIndex& index) const
{
  Qt::ItemFlags flags = QAbstractItemModel::flags(index);

  flags |= Qt::ItemIsEditable;

  // flags ^= Qt::ItemIsSelectable;

  return flags;
}


int
ImportTreeModel::
getEntryPosition(TreeWrapper::TreeEntry* const entry) const
{
  auto it = std::find_if(_lasFileEntries.begin(),
                         _lasFileEntries.end(), 
                         [&](std::unique_ptr<TreeEntry> const & p) { return (p.get() == entry); });

  return it - _lasFileEntries.begin();
}
