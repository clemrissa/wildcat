#ifndef Geo_TypeSystem_Models_CurveTypeEntry_hpp
#define Geo_TypeSystem_Models_CurveTypeEntry_hpp

#include "TreeEntry.hpp"

#include <QtXml/QDomElement>

namespace Geo {
namespace TypeSystem {
namespace Models {
namespace CurveTypes {
//

class CurveTypeEntry: public TreeEntry
{
public:
  CurveTypeEntry(Geo::Domain::CurveType::Shared curveType,
                 TreeEntry*                     parent);

  CurveTypeEntry(QDomElement& domElement,
                 TreeEntry*   parent);

  virtual
  ~CurveTypeEntry();

  virtual QVariant
  data(int role, int column) const override;

protected:
  QString _familyName;
  QString _mnemonics;
  QString _units;
  QString _min;
  QString _max;
};

//
}
}
}
}
#endif // Geo_TypeSystem_Models_CurveTypeEntry_hpp
