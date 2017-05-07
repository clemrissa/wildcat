#include "ConnectionsEditorWidgetModel.hpp"

#include <ComponentManager/Creator>

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
  _connectionsManager =
    ComponentManager::create<ConnectionManager*>("Database.ConnectionManager");

  for (auto connection : _connectionsManager->connections())
    _entries.push_back(new ConnectionEntry(connection));

  // last empty entry ( a placeholder for adding new connections )
  _entries.push_back(new ConnectionEntry());
}


ConnectionsEditorWidgetModel::
~ConnectionsEditorWidgetModel()
{
  qDeleteAll(_entries);
}


QVariant
ConnectionsEditorWidgetModel::
data(const QModelIndex& index, int role) const
{
  Entry* entry =
    static_cast<Entry*>(index.internalPointer());

  return entry->data(role, index.column());
}


QModelIndex
ConnectionsEditorWidgetModel::
index(int row, int column, const QModelIndex& parent) const
{
  return QAbstractItemModel::createIndex(row, column, _entries[row]);
}


QModelIndex
ConnectionsEditorWidgetModel::
parent(const QModelIndex& index) const
{
  Q_UNUSED(index);

  return QModelIndex();
}


int
ConnectionsEditorWidgetModel::
columnCount(const QModelIndex& parent) const
{
  Q_UNUSED(parent);

  return ConnectionEntry::Size;
}


int
ConnectionsEditorWidgetModel::
rowCount(const QModelIndex& parent) const
{
  return _connectionsManager->size() + 1;
}


// bool
// Model::
// insertRows(int row, int count, const QModelIndex& parent) {
////beginInsertRows();

////endInsertRows();
// }

QVariant
ConnectionsEditorWidgetModel::
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
    case ConnectionEntry::Type:
      result = tr("Type");
      break;

    case ConnectionEntry::Database:
      result = tr("Database");
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
      index.column() == ConnectionEntry::CloseAction &&
      index.row() != _entries.size() - 1)
  {
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
