#include "TreeEntry.hpp"

using Geo::TypeSystem::Gui::CurveTypes::TreeEntry;

using Geo::Domain::CurveType;

TreeEntry::
TreeEntry(TreeEntry* parent)
  : _parent(parent)
  , _state(Active)
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
setConnection(std::shared_ptr<IConnection> connection)
{
  _connection = connection;

  for (TreeEntry* e : _entries)
    e->setConnection(connection);
}


void
TreeEntry::
switchState()
{
  switch (_state)
  {
    case Active:
      _state = Deleted;

      break;

    case Deleted:
      _state = Active;

      if (_parent)
        _parent->setParentStateActive();

      break;
  }

  setChildState(_state);
}


void
TreeEntry::
setParentStateActive()
{
  _state = Active;

  if (_parent)
    _parent->setParentStateActive();
}


void
TreeEntry::
setChildState(State state)
{
  _state = state;

  for (TreeEntry* e : _entries)
    e->setChildState(state);
}


void
TreeEntry::
setState(State state)
{
  _state = state;
}
