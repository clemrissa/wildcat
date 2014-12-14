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

  CurveTypeEntry(QDomElement& de,
                 TreeEntry*   parent);

  virtual
  ~CurveTypeEntry();

  virtual QVariant
  data(int role, int column) const override;

  void
  addXmlData(QDomElement& de);

protected:
  QString _familyName;
  QString _curveType;
  QString _mnemonic;
  QString _units;
  QString _min;
  QString _max;
  QString _scale;
};

//
}
}
}
}
#endif // Geo_TypeSystem_Models_CurveTypeEntry_hpp
