#include "WellTraitEntry.hpp"

#include <Uni/Logging/Logging>

using Geo::Database::Models::DatabaseSettingsWidgetModel::WellTraitEntry;

QVariant
WellTraitEntry::
data(int role, int column)
{
  Q_UNUSED(column);

  if (role != Qt::DisplayRole && role != Qt::EditRole)
    return QVariant();

  switch (column) {
  case Trait:
    return _trait->name();
    break;

  case Synonyms: {
    return _trait->getSynonymsAsString();

    break;
  }
  }

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
