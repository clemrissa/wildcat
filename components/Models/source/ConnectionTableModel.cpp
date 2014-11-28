#include "ConnectionTableModel.hpp"

#include <Database/Connections/ConnectionManager>
#include <Database/Connections/Connection>

#include <DependencyManager/ApplicationContext>

#include "ConnectionEntry.hpp"

using Geo::Models::ConnectionEntry;
using Geo::Models::ConnectionTableModel;

ConnectionTableModel::
ConnectionTableModel()
  : ConnectionListModel()
{
}


ConnectionTableModel::
~ConnectionTableModel()
{ }

int
ConnectionTableModel::
columnCount(const QModelIndex& parent) const
{
  Q_UNUSED(parent);

  return ConnectionEntry::Size;
}

QVariant
ConnectionTableModel::
data(const QModelIndex& index, int role) const
{
  ConnectionEntry* entry =
    static_cast<ConnectionEntry*>(index.internalPointer());

  return entry->data(role, index.column());
}

