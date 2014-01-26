#include "ImportTreeModel.hpp"

#include "ImportTreeLasFileModel.hpp"

namespace Geo {
namespace Import {
ImportTreeModel::
ImportTreeModel(QVector<ImportTreeLasFileModel*> importTreeLasFileModels):
  _importTreeLasFileModels(importTreeLasFileModels) {
  //
}

QVariant
ImportTreeModel::
data(const QModelIndex& index, int role) const  {
  QVariant result;

  switch (role) {
  case Qt::DisplayRole: {
    result = tr("Table item");
    break;
  }

  default:
    break;
  }

  return result;
}

QModelIndex
ImportTreeModel::
index(int row, int column, const QModelIndex& parent) const  {
  return QModelIndex();
}

QModelIndex
ImportTreeModel::
parent(const QModelIndex& index) const  {
  return QModelIndex();
}

int
ImportTreeModel::
columnCount(const QModelIndex& parent) const  {
  // it does not matter as this model is a "fake" one
  // the true number of columns is returned my main model attached to a view
  return 0;
}

int
ImportTreeModel::
rowCount(const QModelIndex& parent) const  {
  int count = 0;

  for (ImportTreeLasFileModel* model : _importTreeLasFileModels)
    count += model->rowCount(QModelIndex());

  return count;
}
}
}
