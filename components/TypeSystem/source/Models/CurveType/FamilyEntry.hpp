#ifndef Geo_TypeSystem_Models_FamilyEntry_hpp
#define Geo_TypeSystem_Models_FamilyEntry_hpp

#include "TreeEntry.hpp"

#include <QtCore/QSet>
#include <QtXml/QDomElement>

namespace Geo {
namespace TypeSystem {
namespace Models {
namespace CurveTypes {
//

class FamilyEntry: public TreeEntry
{
public:
  FamilyEntry(Geo::Domain::CurveType::Shared curveType);

  FamilyEntry(QDomElement& domElement);

  virtual
  ~FamilyEntry();

  virtual QVariant
  data(int role, int column) const override;

public:
  /// Fetches Family, checks if it duplicates an existing entry
  /// adds to children if not
  void
  addChild(QDomElement& domElement);

protected:
  QString _mainFamilyName;

  // prevents Family duplicates
  QSet<QString> _curveNames;
};

//
}
}
}
}
#endif // Geo_TypeSystem_Models_FamilyEntry_hpp
