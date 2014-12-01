#ifndef Geo_TypeSystem_Models_CurveTypeModel_hpp
#define Geo_TypeSystem_Models_CurveTypeModel_hpp

#include <QtCore/QAbstractItemModel>
#include <QtCore/QVector>

namespace Geo {
namespace TypeSystem {
namespace Models {
//

class TreeEntry;
class MainFamilyEntry;
//

class CurveTypeModel: public QAbstractItemModel
{
public:
  CurveTypeModel();

  virtual
  ~CurveTypeModel();

  virtual
  QVariant
  data(const QModelIndex& index, int role) const override;

  virtual
  QModelIndex
  index(int row, int column, const QModelIndex& parent) const override;

  bool
  setData(const QModelIndex& index,
          const QVariant&    value,
          int                role = Qt::EditRole) override;

  virtual
  QModelIndex
  parent(const QModelIndex& index) const override;

  virtual
  int
  columnCount(const QModelIndex& parent) const override;

  virtual
  int
  rowCount(const QModelIndex& parent) const override;

  //

  QVariant
  headerData(int             section,
             Qt::Orientation orientation,
             int             role = Qt::DisplayRole) const override;

  Qt::ItemFlags
  flags(const QModelIndex& index) const override;

public:
  void
  loadXml(QString fileName);

private:
  int
  getEntryPosition(TreeEntry* const entry) const;

private:
  QVector<MainFamilyEntry*> _curveTypeEntries;
};

//
}
}
}
#endif // Geo_TypeSystem_Models_CurveTypeModel_hpp
