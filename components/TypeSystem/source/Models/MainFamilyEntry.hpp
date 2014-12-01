#ifndef Geo_TypeSystem_Models_MainFamilyEntry_hpp
#define Geo_TypeSystem_Models_MainFamilyEntry_hpp

#include "TreeEntry.hpp"

#include <QtCore/QSet>
#include <QtXml/QDomElement>

namespace Geo {
namespace TypeSystem {
namespace Models {
//

class MainFamilyEntry: public TreeEntry
{
public:
  MainFamilyEntry(Geo::Domain::CurveType::Shared curveType);

  MainFamilyEntry(QDomElement& domElement);

  virtual
  ~MainFamilyEntry();

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
  QSet<QString> _familyNames;
};

//
}
}
}
#endif // Geo_TypeSystem_Models_MainFamilyEntry_hpp
