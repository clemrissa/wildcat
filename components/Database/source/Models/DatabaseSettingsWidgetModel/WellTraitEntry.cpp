#include "WellTraitEntry.hpp"

#include <QtGui/QIcon>

#include <Uni/Logging/Logging>

using Geo::Database::Models::DatabaseSettingsWidgetModel::WellTraitEntry;

QVariant
WellTraitEntry::
data(int role, int column)
{
  Q_UNUSED(column);

  switch(role) {
  case Qt::DisplayRole:
    return getDisplayEditRole(column);
    break;

  case Qt::EditRole:
    return getDisplayEditRole(column);
    break;

  case Qt::DecorationRole:
    return getDecorationRole(column);
    break;
  }

  return QVariant();
}


QVariant
WellTraitEntry::
getDisplayEditRole(int column) const
{
  QVariant result;

  switch (column) {
  case Trait:
    result = _trait->name();
    break;

  case Synonyms: {
    result = _trait->getSynonymsAsString();

    break;
  }
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
