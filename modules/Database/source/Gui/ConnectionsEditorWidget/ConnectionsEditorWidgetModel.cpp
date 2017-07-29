#include "ConnectionsEditorWidgetModel.hpp"

#include <algorithm>

#include <ComponentManager/Creator>

#include <Connections/ConnectionManager.hpp>

#include "Gui/ConnectionsEditorWidget/ConnectionEntry.hpp"
#include "Gui/ConnectionsEditorWidget/Entry.hpp"

using Geo::Database::ConnectionManager;
using Geo::Database::Gui::ConnectionEntry;
using Geo::Database::Gui::ConnectionsEditorWidgetModel;
using Geo::Database::Gui::Entry;

ConnectionsEditorWidgetModel::
ConnectionsEditorWidgetModel()
{
  _connectionsManager =
    ComponentManager::create<ConnectionManager*>("Database.ConnectionManager");

  for (auto connection : _connectionsManager->connections())
    _entries.emplace_back(new ConnectionEntry(connection));

  // last empty entry ( a placeholder for adding new connections )
  _entries.emplace_back(new ConnectionEntry());
}


ConnectionsEditorWidgetModel::
~ConnectionsEditorWidgetModel()
{}


QVariant
ConnectionsEditorWidgetModel::
data(const QModelIndex& index, int role) const
{
  Q_UNUSED(role);

  Entry* entry = static_cast<Entry*>(index.internalPointer());

  return entry->data(role, index.column());
}


QModelIndex
ConnectionsEditorWidgetModel::
index(int row, int column, const QModelIndex& parent) const
{
  Q_UNUSED(parent);

  return QAbstractItemModel::createIndex(row, column, _entries[row].get());
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
  Q_UNUSED(parent);

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
      index.row() == (int)(_entries.size() - 1))
    flags |= Qt::ItemIsEditable;

  return flags;
}


void
ConnectionsEditorWidgetModel::
addConnection(DatabaseType databaseType)
{
  Q_UNUSED(databaseType);

  std::size_t size = _connectionsManager->size();

  beginInsertRows(QModelIndex(), size, size);

  auto newConnection = _connectionsManager->createConnection(databaseType);

  auto connectionEntry =
    std::unique_ptr<Entry>(new ConnectionEntry(newConnection));

  _entries.insert(_entries.begin() + size,
                  std::move(connectionEntry));

  endInsertRows();
}


void
ConnectionsEditorWidgetModel::
onClicked(const QModelIndex& index)
{
  if (!index.parent().isValid() &&
      index.column() == ConnectionEntry::CloseAction &&
      index.row() != (int)(_entries.size() - 1))
  {
    beginRemoveRows(QModelIndex(), index.row(), index.row());

    _entries.erase(_entries.begin() + index.row());

    _connectionsManager->removeConnection(index.row());
    endRemoveRows();
  }
}


//int
//ConnectionsEditorWidgetModel::
//getEntryPosition(Entry* entry) const
//{
//auto it = std::find(_entries.begin(),
//_entries.end(), entry);

//return it - _entries.begin();
//}
