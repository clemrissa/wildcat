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

  CurveTypeEntry(QString    cureTypeName,
                 TreeEntry* parent);

  // CurveTypeEntry(QDomElement& de,
  // TreeEntry*   parent);

  virtual
  ~CurveTypeEntry();

  virtual QVariant
  data(int role, int column) const override;

  bool
  setData(int column, QVariant value) override;

  QWidget*
  delegateWidget(int column) const override;

  void
  setDataFromWidget(QWidget*            editor,
                    QModelIndex const&  index,
                    QAbstractItemModel* model) override;

  Geo::Domain::CurveType::Shared
  curveType() const { return _curveType; }

  bool
  getPersisted() const { return _persisted; }

  void
  setPersisted(const bool persisted) { _persisted = persisted; }

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

  QVariant
  getBackgroundRole(int column) const;

  QVector<Geo::Domain::Unit::Shared>
  getUnits() const;

  QStringList
  getUnitNames() const;
};

//
}
}
}
}
#endif // Geo_TypeSystem_Models_CurveTypeEntry_hpp
