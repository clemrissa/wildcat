#include "ImportTreeModel.hpp"

#include "ImportTreeLasFileModel.hpp"

#include <Uni/Logging/Logging>

namespace Geo {
namespace Import {
ImportTreeModel::
ImportTreeModel(QVector<ImportTreeLasFileModel*> importTreeLasFileModels):
  QAbstractItemModel(),
  _importTreeLasFileModels(importTreeLasFileModels) {
  //
}

ImportTreeModel::
ImportTreeModel() {
  //
}

void
ImportTreeModel::
setImportTreeLasFileModels(QVector<ImportTreeLasFileModel*> lasFileModels) {
  beginResetModel();
  _importTreeLasFileModels = lasFileModels;
  endResetModel();
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
  if (row >= 2 && column >= 2)
    return QModelIndex();

  return QAbstractItemModel::createIndex(row, column, (void*)0);
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
  return 2;
}

int
ImportTreeModel::
rowCount(const QModelIndex& parent) const  {
  int count = 2;

  return count;

  for (ImportTreeLasFileModel* model : _importTreeLasFileModels)
    count += model->rowCount(QModelIndex());

  return count;
}

QVariant
ImportTreeModel::
headerData(int             section,
           Qt::Orientation orientation,
           int             role)  const {
  //

  switch (orientation) {
  case Qt::Horizontal:

    if (role == Qt::DisplayRole)
      return tr("Column");

    break;

  case Qt::Vertical:
    return tr("Row");
    break;

  default:
    break;
  }

  return QVariant();
}
}
}
