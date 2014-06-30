#ifndef Geo_Database_DatabaseSettingsWidgetModel_WellTrait_hpp
#define Geo_Database_DatabaseSettingsWidgetModel_WellTrait_hpp

#include <Domain/WellTrait>

#include <Models/DatabaseSettingsWidgetModel/Entry.hpp>

namespace Geo {
namespace Database {
namespace Models {
namespace DatabaseSettingsWidgetModel {
//

class WellTraitEntry: public Entry
{
public:
  enum Column { Trait = 0, 
                Synonyms = 1, 
                CloseAction = 2, 
                Size };

public:
  WellTraitEntry(Geo::Domain::WellTrait::Shared trait):
    _trait(trait)
  {
  }

  WellTraitEntry()
  {
  }

  QVariant
  data(int role, int column) override;

  Geo::Domain::WellTrait::Shared
  trait() const;

private:
  Geo::Domain::WellTrait::Shared _trait;

  QVariant
  getDisplayEditRole(int column) const;

  QVariant
  getDecorationRole(int column) const;
};

//
}
}
}
}

#endif //  Geo_Database_DatabaseSettingsWidgetModel_WellTrait_hpp
