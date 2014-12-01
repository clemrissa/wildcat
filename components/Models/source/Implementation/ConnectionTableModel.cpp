#include "ConnectionTableModel.hpp"

#include <Database/Connections/ConnectionManager>
#include <Database/Connections/Connection>

#include <DependencyManager/ApplicationContext>

#include "ConnectionEntry.hpp"

using Geo::Models::Implementation::ConnectionEntry;
using Geo::Models::Implementation::ConnectionTableModel;


ConnectionTableModel::
ConnectionTableModel()
  : ConnectionListModel()
{

}


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

