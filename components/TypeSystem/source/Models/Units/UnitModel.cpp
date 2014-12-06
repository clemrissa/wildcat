#include "UnitModel.hpp"

#include <QtCore/QFile>

#include "UnitTableEntry.hpp"

#include <Domain/Unit>

using Geo::TypeSystem::Models::Units::UnitModel;
using Geo::TypeSystem::Models::Units::UnitTableEntry;

UnitModel::
UnitModel()
{
  reloadUnits();
}


UnitModel::
~UnitModel()
{
  for (UnitTableEntry* entry : _unitEntries)
    delete entry;
}


QVariant
UnitModel::
data(const QModelIndex& index, int role) const
{
  if (!index.isValid())
    return QVariant();

  UnitTableEntry* entry =
    static_cast<UnitTableEntry*>(index.internalPointer());

  return entry->data(role, index.column());
}


QModelIndex
UnitModel::
index(int row, int column, const QModelIndex& parent) const
{
  return QAbstractItemModel::createIndex(row, column,
                                         _unitEntries[row]);
}


bool
UnitModel::
setData(const QModelIndex& index,
        const QVariant&    value,
        int                role)
{
  if (role != Qt::EditRole)
    return false;

  auto treeEntry =
    static_cast<UnitTableEntry*>(index.internalPointer());

  bool result = treeEntry->setData(role, index.column(), value);

  if (result)
    emit dataChanged(index, index);

  return result;
}


QModelIndex
UnitModel::
parent(const QModelIndex& index) const
{
  return QModelIndex();
}


int
UnitModel::
columnCount(const QModelIndex& parent) const
{
  Q_UNUSED(parent);
  return UnitTableEntry::Column::Size;
}


int
UnitModel::
rowCount(const QModelIndex& parent) const
{
  Q_UNUSED(parent);
  return _unitEntries.size();
}


QVariant
UnitModel::
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
  case UnitTableEntry::Name:
    result = tr("Name");
    break;

  case UnitTableEntry::Symbol:
    result = tr("Symbol");
    break;

  case UnitTableEntry::Offset:
    result = tr("Offset");
    break;

  case UnitTableEntry::Scale:
    result = tr("Scale");
    break;

  case UnitTableEntry::Dimensions:
    result = tr("Dimensions");
    break;

  default:
    result = QVariant();
    break;
  }

  return result;
}


Qt::ItemFlags
UnitModel::
flags(const QModelIndex& index) const
{
  Qt::ItemFlags flags = QAbstractItemModel::flags(index);

  // flags |= Qt::ItemIsEditable;

  // flags ^= Qt::ItemIsSelectable;

  return flags;
}


void
UnitModel::
loadXml(QString fileName)
{
  Q_UNUSED(fileName);
}


void
UnitModel::
setConnection(Database::Connections::Connection::Shared connection)
{
  // if (!_connection.isNull())
  // saveTraits();

  _connection = connection;

  reloadUnits();
}


int
UnitModel::
getEntryPosition(UnitTableEntry* const entry) const
{
  auto it = std::find(_unitEntries.begin(),
                      _unitEntries.end(), entry);

  return it - _unitEntries.begin();
  //
}


void
UnitModel::
reloadUnits()
{
  if (_connection.isNull())
    return;

  beginResetModel();
  {
    qDeleteAll(_unitEntries);
    _unitEntries.resize(0);

    using Geo::Domain::Unit;

    auto dataAccessFactory = _connection->dataAccessFactory();

    auto unitAccess = dataAccessFactory->unitAccess();

    QVector<Unit::Shared> traits = unitAccess->findAll();

    for (Unit::Shared t : traits)
      _unitEntries.append(new UnitTableEntry(t));

    // we add one more empty trait
    Unit::Shared emptyTrait(new Unit());

    _unitEntries.append(new UnitTableEntry(emptyTrait));
  }
  endResetModel();
  //
}
