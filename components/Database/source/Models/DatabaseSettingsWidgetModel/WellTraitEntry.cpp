#include "TraitEntry.hpp"


using Geo::Database::Models::DatabaseSettingsWidgetModel::WellTraitEntry;


QVariant
WellTraitEntry::
data(int role, int column) {

  return QVariant;
}

Geo::Domain::WellTrait::Shared
WellTraitEntry::
connection()
{
  return _trait;
}


  //QVariant
//WellTraitEntry::
  //getDisplayRole(int column);

  //QVariant
//WellTraitEntry::
  //getBackgroundRole(int column);
