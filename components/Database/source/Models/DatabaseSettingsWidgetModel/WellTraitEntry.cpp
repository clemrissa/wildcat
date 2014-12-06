#include "WellTraitEntry.hpp"

#include <QtGui/QIcon>

#include <Uni/Logging/Logging>

using Geo::Database::Models::DatabaseSettingsWidgetModel::WellTraitEntry;

QVariant
WellTraitEntry::
data(int role, int column)
{
  using Domain::WellTrait;

  if (!_trait->isValid())
    return QVariant();

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
    return QIcon(":/delete.png");

  return QVariant();
}


Geo::Domain::WellTrait::Shared
WellTraitEntry::
trait() const
{
  return _trait;
}


// QVariant
// WellTraitEntry::
// getDisplayRole(int column);

// QVariant
// WellTraitEntry::
// getBackgroundRole(int column);
