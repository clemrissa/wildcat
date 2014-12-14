#include "TreeEntry.hpp"

using Geo::TypeSystem::Models::CurveTypes::TreeEntry;

using Geo::Domain::CurveType;

TreeEntry::
TreeEntry(CurveType::Shared curveType,
          TreeEntry*        parent):
  _parent(parent),
  _curveType(curveType),
  _state(Active)
{
  //
}


TreeEntry::
TreeEntry(TreeEntry* parent):
  _parent(parent),
  _state(Active)
{
  //
}


// TreeEntry::
// TreeEntry():
// _parent(nullptr)
// _state(Active),
// {
////
// }

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


void
TreeEntry::
switchState()
{
  switch (_state) {
  case Active:
    _state = Deleted;
    break;

  case Deleted:
    _state = Active;
    break;
  }

  for (TreeEntry* e : _entries)
    e->switchState();
}


QWidget*
TreeEntry::
delegateWidget(int column) const
{
  Q_UNUSED(column);
  return nullptr;
}
