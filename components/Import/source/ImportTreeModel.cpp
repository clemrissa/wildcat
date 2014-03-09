#include "ImportTreeModel.hpp"

#include "ImportTreeLasFileModel.hpp"

#include <Uni/Logging/Logging>

#include <QSharedPointer>

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
  INFO << "IMPORTED " << lasFileModels.size() << " las files";
  _importTreeLasFileModels = lasFileModels;
  endResetModel();
}

QVariant
ImportTreeModel::
data(const QModelIndex& index, int role) const  {
  QVariant result;

  if (role != Qt::DisplayRole)
    return result;

  QSharedPointer<LasFile> const& lasFile = _importTreeLasFileModels[index.row()]->getLasFile();

  switch (index.column()) {
  case 0:
    result = lasFile->wellInformation.wellName;
    break;
  }

  return result;
}

QModelIndex
ImportTreeModel::
index(int row, int column, const QModelIndex& parent) const  {
  if (row >= _importTreeLasFileModels.size() && column >= 4)
    return QModelIndex();

  return QAbstractItemModel::createIndex(row, column, row);
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
  return 4;
}

int
ImportTreeModel::
rowCount(const QModelIndex& parent) const {
  int count = 0;

  for (ImportTreeLasFileModel* model : _importTreeLasFileModels) {
    ++count;
    Q_UNUSED(model);
  }

  // count += model->rowCount(QModelIndex());

  return count;
}

QVariant
ImportTreeModel::
headerData(int             section,
           Qt::Orientation orientation,
           int             role)  const {
  QVariant result;

  if (role != Qt::DisplayRole)
    return result;

  if (orientation == Qt::Vertical)
    return result;

  switch (section) {
  case 0:
    result = tr("Item");
    break;

  case 1:
    result = tr("Value(Name)");
    break;

  case 2:
    result = tr("Parsed Units");
    break;

  case 3:
    result = tr("Save Units");
    break;
  }

  return result;
}
}
}
