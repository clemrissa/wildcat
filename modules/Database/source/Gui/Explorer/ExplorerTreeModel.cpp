#include "ExplorerTreeModel.hpp"

#include "ExplorerEntry.hpp"

#include "CategoryEntry.hpp"

namespace Geo
{
namespace Database
{
namespace Gui
{

ExplorerTreeModel::
ExplorerTreeModel()
{
  _explorerEntries.push_back(std::make_unique<CategoryEntry>("Wells"));
  _explorerEntries.push_back(std::make_unique<CategoryEntry>("Las Files"));
  _explorerEntries.push_back(std::make_unique<CategoryEntry>("Units"));
  _explorerEntries.push_back(std::make_unique<CategoryEntry>("Well Traits"));
}


ExplorerTreeModel::
~ExplorerTreeModel()
{
//
}


QVariant
ExplorerTreeModel::
data(const QModelIndex& index, int role) const
{
  if (!index.isValid())
    return QVariant();

  ExplorerEntry* entry =
    static_cast<ExplorerEntry*>(index.internalPointer());

  return entry->data(role, index.column());
}


QModelIndex
ExplorerTreeModel::
index(int row, int column, const QModelIndex& parent) const
{
  if (!parent.isValid())
    return QAbstractItemModel::createIndex(row, column,
                                           _explorerEntries[row].get());

  ExplorerEntry* entry =
    static_cast<ExplorerEntry*>(parent.internalPointer());

  if (entry->entries().size() == 0)
    return QModelIndex();

  return QAbstractItemModel::createIndex(row, column,
                                         entry->entries()[row].get());
}


bool
ExplorerTreeModel::
setData(QModelIndex const & index,
        QVariant const &    value,
        int role)
{
  if (role != Qt::EditRole)
    return false;

  auto treeEntry =
    static_cast<ExplorerEntry*>(index.internalPointer());

  bool result = treeEntry->setData(role, index.column(), value);

  if (result)
    emit dataChanged(index, index);

  return result;
}


QModelIndex
ExplorerTreeModel::
parent(QModelIndex const & index) const
{
  ExplorerEntry* entry =
    static_cast<ExplorerEntry*>(index.internalPointer());

  Q_ASSERT(entry);

  ExplorerEntry* parentEntry = entry->parent();

  if (parentEntry == nullptr)
    return QModelIndex();

  ExplorerEntry* parentParentEntry = parentEntry->parent();

  int position = 0;

  if (parentParentEntry == nullptr)
    position = getEntryPosition(parentEntry);
  else
    position = parentParentEntry->positionOfChildEntry(parentEntry);

  return QAbstractItemModel::createIndex(position, 0, parentEntry);
}


int
ExplorerTreeModel::
columnCount(QModelIndex const & parent) const
{
  Q_UNUSED(parent);
  return ExplorerEntry::Size;
}


int
ExplorerTreeModel::
rowCount(QModelIndex const & parent) const
{
  if (!parent.isValid())
    return _explorerEntries.size();

  ExplorerEntry* entry =
    static_cast<ExplorerEntry*>(parent.internalPointer());

  return entry->entries().size();
}


//

QVariant
ExplorerTreeModel::
headerData(int section,
           Qt::Orientation orientation,
           int role) const
{
  QVariant result;

  if (role != Qt::DisplayRole)
    return result;

  if (orientation == Qt::Vertical)
    return result;

  switch (section)
  {
    case ExplorerEntry::Category:
      result = tr("Category");
      break;

    case ExplorerEntry::Description:
      result = tr("Description");
      break;
  }

  return result;
}


Qt::ItemFlags
ExplorerTreeModel::
flags(QModelIndex const & index) const
{
  Qt::ItemFlags flags = QAbstractItemModel::flags(index);

  //flags |= Qt::ItemIsEditable;

  flags |= Qt::ItemIsSelectable;

  return flags;
}

int
ExplorerTreeModel::
getEntryPosition(ExplorerEntry const * entry) const
{
  auto it = std::find_if(_explorerEntries.begin(),
                         _explorerEntries.end(), 
                         [&](std::unique_ptr<ExplorerEntry> const & p)
                         { return (p.get() == entry); });

  return it - _explorerEntries.begin();
}


//
}
}
}
