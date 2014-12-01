#ifndef Geo_TypeSystem_TreeWrapper_MainFamilyEntry_hpp
#define Geo_TypeSystem_TreeWrapper_MainFamilyEntry_hpp

#include "TreeEntry.hpp"


namespace Geo {
namespace TypeSystem {
namespace Models {
//

class MainFamily: public TreeEntry
{
public:
  MainFamily(Geo::Domain::CurveType::Shared curveType);

  virtual
  ~MainFamily();


  virtual QVariant
  data(int role, int column) const override;

protected:
  QString mainFamilyName;
};

//
}
}
}
#endif // Geo_TypeSystem_TreeWrapper_MainFamilyEntry_hpp
