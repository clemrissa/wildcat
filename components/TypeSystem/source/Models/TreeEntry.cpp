#include "TreeEntry.hpp"

using Geo::TypeSystem::Models::TreeEntry;

using Geo::Domain::CurveType;

TreeEntry::
TreeEntry(CurveType::Shared curveType,
          TreeEntry*        parent):
  _parent(parent),
  _curveType(curveType)
{
  //
}


TreeEntry::
~TreeEntry()
{
  for (TreeEntry* entry : _entries)
    delete entry;
}


int
TreeEntry::
positionOfChildEntry(TreeEntry* const childEntry) const
{
  auto it = std::find(_entries.begin(),
                      _entries.end(),
                      childEntry);

  return it - _entries.begin();
}


void
TreeEntry::
setConnection(Database::Connections::Connection::Shared connection)
{
  _connection = connection;

  for (TreeEntry* e : _entries)
    e->setConnection(connection);
}


QWidget*
TreeEntry::
delegateWidget(int column) const
{
  Q_UNUSED(column);
  return nullptr;
}
