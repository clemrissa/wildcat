#ifndef Geo_TypeSystem_Models_CurveTypeEntry_hpp
#define Geo_TypeSystem_Models_CurveTypeEntry_hpp

#include "TreeEntry.hpp"

#include <QtXml/QDomElement>

#include <Domain/CurveType>

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

public:
  void
  addXmlData(QDomElement& de);

  QDomElement
  getXmlDescription(QDomDocument& doc) override;

private:
  Geo::Domain::CurveType::Shared _curveType;

  bool _persisted;

  QString _scale;
  QString _continuity;

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
#endif // Geo_TypeSystem_Models_CurveTypeEntry_hpp
