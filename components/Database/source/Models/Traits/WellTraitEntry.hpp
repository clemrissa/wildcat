#ifndef Geo_Database_Traits_WellTrait_hpp
#define Geo_Database_Traits_WellTrait_hpp

#include <Database/Connections/Connection>
#include <Domain/WellTrait>

#include <Models/Traits/Entry.hpp>

namespace Geo {
namespace Database {
namespace Models {
namespace Traits {
//

class WellTraitEntry: public Entry
{
public:
  enum Column { Trait       = 0,
                Synonyms    = 1,
                Type        = 2,
                CloseAction = 3,
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
  getDisplayOrEditRole(int column) const;

  QVariant
  getDecorationRole(int column) const;
};

//
}
}
}
}

#endif //  Geo_Database_Traits_WellTrait_hpp
