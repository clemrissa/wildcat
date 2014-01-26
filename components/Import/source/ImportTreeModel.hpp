#ifndef _GeoImport_ImportTreeModel_hpp_
#define _GeoImport_ImportTreeModel_hpp_

#include <QAbstractItemModel>
#include <QVector>

namespace Geo {
namespace Import {
class ImportTreeLasFileModel;

class ImportTreeModel: public QAbstractItemModel {
public:
  ImportTreeModel(QVector<ImportTreeLasFileModel*> importTreeLasFileModels);

public:
  QVariant
  data(const QModelIndex& index, int role) const override;

  QModelIndex
  index(int row, int column, const QModelIndex& parent) const override;

  QModelIndex
  parent(const QModelIndex& index) const override;

  int
  columnCount(const QModelIndex& parent) const override;

  int
  rowCount(const QModelIndex& parent) const override;

private:
  QVector<ImportTreeLasFileModel*> _importTreeLasFileModels;
};
}
}

#endif //  _GeoImport_ImportTreeModel_hpp_
