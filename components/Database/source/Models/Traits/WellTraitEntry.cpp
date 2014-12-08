#include "WellTraitEntry.hpp"

#include <QtGui/QIcon>
#include <QtGui/QPalette>

#include <Uni/Logging/Logging>

using Geo::Database::Models::Traits::WellTraitEntry;

WellTraitEntry::
WellTraitEntry(Geo::Domain::WellTrait::Shared trait):
  _trait(trait),
  _state(Active),
  _persisted(trait->isValid())
{
}


// WellTraitEntry::
// WellTraitEntry()
// {
// }

QVariant
WellTraitEntry::
data(int role, int column)
{
  using Domain::WellTrait;

  switch (role) {
  case Qt::DisplayRole:
    return getDisplayOrEditRole(column);
    break;

  case Qt::EditRole:
    return getDisplayOrEditRole(column);
    break;

  case Qt::DecorationRole:

    if (!_trait->isValid())
      return QVariant();
    else
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


QVariant
WellTraitEntry::
getDisplayOrEditRole(int column) const
{
  QVariant result;

  using Domain::WellTrait;

  switch (column) {
  case Trait:
    result = _trait->name();
    break;

  case Synonyms:
    result = _trait->getSynonymsAsString();
    break;

  case Type:
    result = WellTrait::typeAsString(_trait->type());
    break;
  }

  return result;
}


QVariant
WellTraitEntry::
getDecorationRole(int column) const
{
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
WellTraitEntry::
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


Geo::Domain::WellTrait::Shared
WellTraitEntry::
trait() const
{
  return _trait;
}


void
WellTraitEntry::
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


// QVariant
// WellTraitEntry::
// getDisplayRole(int column);

// QVariant
// WellTraitEntry::
// getBackgroundRole(int column);
