#include "SettingsTreeModel.hpp"

#include <DependencyManager/ApplicationContext>

#include <Uni/Logging/Logging>

#include "ConnectionManager.hpp"
#include "SettingsTreeConnection.hpp"
#include "SettingsTreeEntry.hpp"

#include <algorithm>

using Geo::Database::SettingsTreeModel;

SettingsTreeModel::
SettingsTreeModel()
{
  using DependencyManager::ApplicationContext;

  _connectionsManager =
    ApplicationContext::create<ConnectionManager>("Database.ConnectionManager");

  for (auto connection : _connectionsManager->connections())
    _entries.push_back(new SettingsTreeConnection(connection));

  // last empty entry ( a placeholder for adding new connections )
  _entries.push_back(new SettingsTreeConnection());
}


SettingsTreeModel::
~SettingsTreeModel()
{
  for (auto entry : _entries)
    delete entry;
}


QVariant
SettingsTreeModel::
data(const QModelIndex& index, int role) const
{
  if (!index.isValid())
    return QVariant();

  SettingsTreeEntry* entry =
    static_cast<SettingsTreeEntry*>(index.internalPointer());

  return entry->data(role, index.column());
}


QModelIndex
SettingsTreeModel::
index(int row, int column, const QModelIndex& parent) const
{
  if (!parent.isValid())
    return QAbstractItemModel::createIndex(row, column, _entries[row]);

  SettingsTreeEntry* entry =
    static_cast<SettingsTreeEntry*>(parent.internalPointer());

  if (entry->entries().size() == 0)
    return QModelIndex();

  return QAbstractItemModel::createIndex(row, column, entry->entries()[row]);
}


QModelIndex
SettingsTreeModel::
parent(const QModelIndex& index) const
{
  SettingsTreeEntry* entry =
    static_cast<SettingsTreeEntry*>(index.internalPointer());

  Q_ASSERT(entry);

  SettingsTreeEntry* parentEntry = entry->parent();

  if (parentEntry == nullptr)
    return QModelIndex();

  SettingsTreeEntry* parentParentEntry = parentEntry->parent();

  int position = 0;

  if (parentParentEntry == nullptr)
    position = getEntryPosition(parentEntry);
  else
    position =  parentParentEntry->positionOfChildEntry(parentEntry);

  return QAbstractItemModel::createIndex(position, 0, parentEntry);
}


int
SettingsTreeModel::
columnCount(const QModelIndex& parent) const
{
  return 2;
}


int
SettingsTreeModel::
rowCount(const QModelIndex& parent) const
{
  if (!parent.isValid())
    return _connectionsManager->size() + 1;

  SettingsTreeEntry* entry =
    static_cast<SettingsTreeEntry*>(parent.internalPointer());

  return entry->entries().size();
}


// bool
// SettingsTreeModel::
// insertRows(int row, int count, const QModelIndex& parent) {
////beginInsertRows();

////endInsertRows();
// }

QVariant
SettingsTreeModel::
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
  case SettingsTreeEntry::Database:
    result = tr("Item");
    break;

  default:
    result = QVariant();
    break;
  }

  return result;
}


Qt::ItemFlags
SettingsTreeModel::
flags(const QModelIndex& index) const
{
  if (!index.isValid())
    return 0;

  Qt::ItemFlags flags = QAbstractItemModel::flags(index);

  if (!index.parent().isValid() &&
      index.row() == _entries.size() - 1)
    flags |= Qt::ItemIsEditable;

  return flags;
}


void
SettingsTreeModel::
addConnection(DatabaseType databaseType)
{
  int size = _connectionsManager->size();
  beginInsertRows(QModelIndex(), size, size);

  _connectionsManager->createConnection();
  // switch(c->currentIndex()) {
  // case DatabaseType::MySql:
  // break;
  // case DatabaseType::SQLite:
  // break;
  // }
  _entries.insert(size, new SettingsTreeConnection(_connectionsManager->operator[](size)));

  endInsertRows();
}


void
SettingsTreeModel::
onClicked(const QModelIndex& index)
{
  if (!index.parent().isValid() &&
      index.column() == 1 &&
      index.row() != _entries.size() - 1) {
    beginRemoveRows(QModelIndex(), index.row(), index.row());
    auto connectionWrapper = _entries.takeAt(index.row());
    delete connectionWrapper;

    _connectionsManager->removeConnection(index.row());
    endRemoveRows();
  }
}


int
SettingsTreeModel::
getEntryPosition(SettingsTreeEntry* entry) const
{
  auto it = std::find(_entries.begin(),
                      _entries.end(), entry);

  return it - _entries.begin();
}
