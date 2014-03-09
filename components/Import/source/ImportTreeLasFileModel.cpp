#include "ImportTreeLasFileModel.hpp"

namespace Geo {
namespace Import {
QVariant
ImportTreeLasFileModel::
data(const QModelIndex& index, int role) const  {
  return QVariant();
}

QModelIndex
ImportTreeLasFileModel::
index(int row, int column, const QModelIndex& parent) const  {
  return QModelIndex();
}

QModelIndex
ImportTreeLasFileModel::
parent(const QModelIndex& index) const  {
  return QModelIndex();
}

int
ImportTreeLasFileModel::
columnCount(const QModelIndex& parent) const  {
  return 0;
}

int
ImportTreeLasFileModel::
rowCount(const QModelIndex& parent = QModelIndex()) const  {
  return 0;
}

LasFile const&
ImportTreeLasFileModel::
getLasFile() const {
  return _lasFile;
}
}
}
