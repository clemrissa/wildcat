#include "DimensionsEditorModel.hpp"

using Geo::TypeSystem::Models::DimensionsEditorModel;

DimensionsEditorModel::
DimensionsEditorModel(Geo::Domain::Dimensions& dimensions):
  _dimensions(dimensions)
{
  //
}


DimensionsEditorModel::
~DimensionsEditorModel()
{
}


QVariant
DimensionsEditorModel::
data(const QModelIndex& index, int role) const
{
  if (role != Qt::DisplayRole)
    return QVariant();

  return QString("Ololo");
}


QModelIndex
DimensionsEditorModel::
index(int row, int column, const QModelIndex& parent) const
{
  return QAbstractItemModel::createIndex(row, column, row);
}


bool
DimensionsEditorModel::
setData(const QModelIndex& index,
        const QVariant&    value,
        int                role)
{
  return false;
}


QModelIndex
DimensionsEditorModel::
parent(const QModelIndex& index) const
{
  Q_UNUSED(index);

  return QModelIndex();
}


int
DimensionsEditorModel::
columnCount(const QModelIndex& parent) const
{
  Q_UNUSED(parent);

  return 1;
}


int
DimensionsEditorModel::
rowCount(const QModelIndex& parent) const
{
  // return Geo::Domain::Dimensions::FundamentalUnitsSize;

  return 5;
}


QVariant
DimensionsEditorModel::
headerData(int             section,
           Qt::Orientation orientation,
           int             role)  const
{
  QVariant result;

  // if (role != Qt::DisplayRole)
  return result;
}


Qt::ItemFlags
DimensionsEditorModel::
flags(const QModelIndex& index) const
{
  return QAbstractItemModel::flags(index);
}
