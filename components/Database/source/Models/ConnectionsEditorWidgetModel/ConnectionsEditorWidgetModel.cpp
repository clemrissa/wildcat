#include "ConnectionsEditorWidgetModel.hpp"

#include <DependencyManager/ApplicationContext>

#include <Uni/Logging/Logging>

#include <Connections/ConnectionManager.hpp>

#include <Models/ConnectionsEditorWidgetModel/ConnectionEntry.hpp>
#include <Models/ConnectionsEditorWidgetModel/Entry.hpp>

#include <algorithm>

using Geo::Database::Connections::ConnectionManager;
using Geo::Database::Models::ConnectionsEditorWidgetModel::ConnectionEntry;
using Geo::Database::Models::ConnectionsEditorWidgetModel::
      ConnectionsEditorWidgetModel;
using Geo::Database::Models::ConnectionsEditorWidgetModel::Entry;

ConnectionsEditorWidgetModel::
ConnectionsEditorWidgetModel()
{
  using DependencyManager::ApplicationContext;

  _connectionsManager =
    ApplicationContext::create<ConnectionManager>("Database.ConnectionManager");

  for (auto connection : _connectionsManager->connections())
    _entries.push_back(new ConnectionEntry(connection));

  // last empty entry ( a placeholder for adding new connections )
  _entries.push_back(new ConnectionEntry());
}


ConnectionsEditorWidgetModel::
~ConnectionsEditorWidgetModel()
{
  for (auto entry : _entries)
    delete entry;
}


QVariant
ConnectionsEditorWidgetModel::
data(const QModelIndex& index, int role) const
{
  if (!index.isValid())
    return QVariant();

  Entry* entry =
    static_cast<Entry*>(index.internalPointer());

  return entry->data(role, index.column());
}


QModelIndex
ConnectionsEditorWidgetModel::
index(int row, int column, const QModelIndex& parent) const
{
  if (!parent.isValid())
    return QAbstractItemModel::createIndex(row, column, _entries[row]);

  Entry* entry =
    static_cast<Entry*>(parent.internalPointer());

  if (entry->entries().size() == 0)
    return QModelIndex();

  return QAbstractItemModel::createIndex(row, column, entry->entries()[row]);
}


QModelIndex
ConnectionsEditorWidgetModel::
parent(const QModelIndex& index) const
{
  Entry* entry =
    static_cast<Entry*>(index.internalPointer());

  Q_ASSERT(entry);

  Entry* parentEntry = entry->parent();

  if (parentEntry == nullptr)
    return QModelIndex();

  Entry* parentParentEntry = parentEntry->parent();

  int position = 0;

  if (parentParentEntry == nullptr)
    position = getEntryPosition(parentEntry);
  else
    position =  parentParentEntry->positionOfChildEntry(parentEntry);

  return QAbstractItemModel::createIndex(position, 0, parentEntry);
}


int
ConnectionsEditorWidgetModel::
columnCount(const QModelIndex& parent) const
{
  Q_UNUSED(parent);

  return 2;
}


int
ConnectionsEditorWidgetModel::
rowCount(const QModelIndex& parent) const
{
  if (!parent.isValid())
    return _connectionsManager->size() + 1;

  Entry* entry =
    static_cast<Entry*>(parent.internalPointer());

  return entry->entries().size();
}


// bool
// Model::
// insertRows(int row, int count, const QModelIndex& parent) {
////beginInsertRows();

////endInsertRows();
// }

QVariant
ConnectionsEditorWidgetModel::
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
  case ConnectionEntry::Database:
    result = tr("Item");
    break;

  default:
    result = QVariant();
    break;
  }

  return result;
}


Qt::ItemFlags
ConnectionsEditorWidgetModel::
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
ConnectionsEditorWidgetModel::
addConnection(Connections::DatabaseType databaseType)
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
  _entries.insert(size,
                  new ConnectionEntry(_connectionsManager->operator[](size)));

  endInsertRows();
}


void
ConnectionsEditorWidgetModel::
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
ConnectionsEditorWidgetModel::
getEntryPosition(Entry* entry) const
{
  auto it = std::find(_entries.begin(),
                      _entries.end(), entry);

  return it - _entries.begin();
}
