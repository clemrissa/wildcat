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
  return QVariant();
}


QModelIndex
DimensionsEditorModel::
index(int row, int column, const QModelIndex& parent) const
{
  // return QAbstractItemModel::createIndex(row, column, _entries[row]);
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
  return _connectionsManager->size();
}


QVariant
DimensionsEditorModel::
headerData(int             section,
           Qt::Orientation orientation,
           int             role)  const
{
  QVariant result;

  if (role != Qt::DisplayRole)
    return result;

  if (orientation == Qt::Vertical)
    return result;

  switch (section) {
  case ConnectionEntry::Type:
    result = tr("Type");
    break;

  case ConnectionEntry::Database:
    result = tr("Database");
    break;

  default:
    result = QVariant();
    break;
  }

  return result;
}


Qt::ItemFlags
DimensionsEditorModel::
flags(const QModelIndex& index) const
{
  return QAbstractItemModel::flags(index);
}
