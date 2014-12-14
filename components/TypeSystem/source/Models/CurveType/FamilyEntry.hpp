#ifndef Geo_TypeSystem_Models_FamilyEntry_hpp
#define Geo_TypeSystem_Models_FamilyEntry_hpp

#include "TreeEntry.hpp"

#include <QtCore/QMap>
#include <QtXml/QDomElement>

namespace Geo {
namespace TypeSystem {
namespace Models {
namespace CurveTypes {
//

class CurveTypeEntry;

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
  QString _familyName;

  // prevents Family duplicates
  QMap<QString, CurveTypeEntry*> _curveTypes;

private:
  QVariant
  getDisplayOrEditRole(int column) const;

  QVariant
  getDecorationRole(int column) const;

  QVariant
  getForegroundRole(int column) const;
};

//
}
}
}
}
#endif // Geo_TypeSystem_Models_FamilyEntry_hpp
