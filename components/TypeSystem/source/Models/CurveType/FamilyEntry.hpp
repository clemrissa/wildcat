#ifndef Geo_TypeSystem_Models_FamilyEntry_hpp
#define Geo_TypeSystem_Models_FamilyEntry_hpp

#include "TreeEntry.hpp"

#include <QtXml/QDomElement>

namespace Geo {
namespace TypeSystem {
namespace Models {
namespace CurveTypes {
//

class FamilyEntry: public TreeEntry
{
public:
  FamilyEntry(Geo::Domain::CurveType::Shared curveType,
              TreeEntry*                     parent);

  FamilyEntry(QDomElement& domElement,
              TreeEntry*   parent);

  virtual
  ~FamilyEntry();

  virtual QVariant
  data(int role, int column) const override;

protected:
  QString _familyName;
};

//
}
}
}
}
#endif // Geo_TypeSystem_Models_FamilyEntry_hpp
