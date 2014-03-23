#include "DatabaseSettingsTreeModel.hpp"

#include <DependencyManager/ApplicationContext>

#include "ConnectionsManager.hpp"
#include "DatabaseSettingsTreeConnection.hpp"
#include "DatabaseSettingsTreeEntry.hpp"

using Geo::Database::DatabaseSettingsTreeModel;

DatabaseSettingsTreeModel::
DatabaseSettingsTreeModel() {
  using DependencyManager::ApplicationContext;

  _connectionsManager =
    ApplicationContext::create<ConnectionsManager>("Database.ConnectionsManager");
  //
}

QVariant
DatabaseSettingsTreeModel::
data(const QModelIndex& index, int role) const  {
  if (!index.isValid())
    return QVariant();

  DatabaseSettingsTreeEntry* entry =
    static_cast<DatabaseSettingsTreeEntry*>(index.internalPointer());

  return entry->data(role, index.column());
}

QModelIndex
DatabaseSettingsTreeModel::
index(int row, int column, const QModelIndex& parent) const {
  if (!parent.isValid()) {
    auto connection =
      new DatabaseSettingsTreeConnection((*_connectionsManager)[row]);

    return QAbstractItemModel::createIndex(row, column,
                                           connection);
  }
}
