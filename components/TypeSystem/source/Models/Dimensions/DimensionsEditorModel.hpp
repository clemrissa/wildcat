#ifndef Geo_TypeSystem_Models_DimensionsEditorModel_hpp
#define Geo_TypeSystem_Models_DimensionsEditorModel_hpp

#include <QtCore/QAbstractItemModel>
#include <QtCore/QVector>

#include <Database/Connections/Connection>
#include <Database/Mixin/ConnectionAcceptor>

#include <Domain/Dimensions>

namespace Geo {
namespace TypeSystem {
namespace Models {
//

class DimensionsEditorModel: public QAbstractItemModel
{
  Q_OBJECT

public:
  DimensionsEditorModel(Domain::Dimensions& dimensions);

  virtual
  ~DimensionsEditorModel();

  virtual
  QVariant
  data(const QModelIndex& index, int role) const override;

  virtual
  QModelIndex
  index(int row, int column, const QModelIndex& parent =
          QModelIndex()) const override;

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

private:
  Geo::Domain::Dimensions& _dimensions;
};

//
}
}
}
#endif // Geo_TypeSystem_Models_DimensionsEditorModel_hpp
