#include "UnitTableEntry.hpp"

#include <QtGui/QIcon>

using Geo::TypeSystem::Models::Units::UnitTableEntry;

using Geo::Domain::Unit;

UnitTableEntry::
UnitTableEntry(Unit::Shared    unit,
               UnitTableEntry* parent):
  _parent(parent),
  _unit(unit),
  _state(Active),
  _persisted(unit->isValid())
{
  //
}


UnitTableEntry::
~UnitTableEntry()
{
  for (UnitTableEntry* entry : _entries)
    delete entry;
}

Geo::Domain::Unit::Shared
UnitTableEntry::
unit() const
{
  return _unit;
}


int
UnitTableEntry::
positionOfChildEntry(UnitTableEntry* const childEntry) const
{
  auto it = std::find(_entries.begin(),
                      _entries.end(),
                      childEntry);

  return it - _entries.begin();
}


QVariant
UnitTableEntry::
data(int role, int column) const
{
  switch (role) {
  case Qt::DisplayRole:
    return getDisplayOrEditRole(column);
    break;

  case Qt::EditRole:
    return getDisplayOrEditRole(column);
    break;

  case Qt::DecorationRole:
    return getDecorationRole(column);
    break;

  case Qt::ForegroundRole:
    return getForegroundRole(column);
    break;

  default:
    return QVariant();
    break;
  }

  return QVariant();
}


void
UnitTableEntry::
setConnection(Database::Connections::Connection::Shared connection)
{
  _connection = connection;

  for (UnitTableEntry* e : _entries)
    e->setConnection(connection);
}


void
UnitTableEntry::
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
}


QWidget*
UnitTableEntry::
delegateWidget(int column) const
{
  Q_UNUSED(column);
  return nullptr;
}


// -----------------

QVariant
UnitTableEntry::
getDisplayOrEditRole(int column) const
{
  QVariant result;

  switch (column) {
  case UnitTableEntry::Name:
    result = _unit->getName();
    break;

  case UnitTableEntry::Symbol:
    result = _unit->getSymbol();
    break;

  case UnitTableEntry::Scale:
    result = _unit->getScale();
    break;

  case UnitTableEntry::Offset:
    result = _unit->getOffset();
    break;

  case UnitTableEntry::Dimensions:
    result = _unit->getDimensions().getFundamentalAsString();

  default:
    break;
  }

  return result;
}


QVariant
UnitTableEntry::
getDecorationRole(int column) const
{
  if (!_unit->isValid())
    return QVariant();

  if (column == CloseAction)

    switch (_state) {
    case Active:
      return QIcon(":/delete.png");
      break;

    case Deleted:
      return QIcon(":/revert.png");
      break;
    }

  return QVariant();
}


QVariant
UnitTableEntry::
getForegroundRole(int column) const
{
  Q_UNUSED(column);

  QVariant result;

  switch (_state) {
  case Active: {
    QPalette palette;
    result =  QColor(palette.color(QPalette::WindowText));
    break;
  }

  case Deleted:
    result = QColor(Qt::lightGray);
    break;
  }

  return result;
}