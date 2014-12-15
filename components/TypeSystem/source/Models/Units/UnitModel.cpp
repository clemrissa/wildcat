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
  deleteMarkedEntries();

  qDeleteAll(_unitEntries);
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
  Q_UNUSED(parent);
  return QAbstractItemModel::createIndex(row, column,
                                         _unitEntries[row]);
}


bool
UnitModel::
setData(const QModelIndex& index,
        const QVariant&    value,
        int                role)
{
  using Geo::Domain::Unit;

  if (role != Qt::EditRole)
    return false;

  auto unitEntry =
    static_cast<UnitTableEntry*>(index.internalPointer());

  bool oldUnitStatus = unitEntry->unit()->isValid();

  switch (index.column()) {
  case UnitTableEntry::Name:
    unitEntry->unit()->setName(value.toString());
    break;

  case UnitTableEntry::Symbol:
    unitEntry->unit()->setSymbol(value.toString());
    break;

  case UnitTableEntry::Scale: {
    bool ok;
    unitEntry->unit()->setScale(value.toDouble(&ok));
    break;
  }

  case UnitTableEntry::Offset: {
    bool ok;
    unitEntry->unit()->setOffset(value.toDouble(&ok));
    break;
  }

  default:
    // fake dimensions set falls here
    break;
  }

  bool newUnitStatus = unitEntry->unit()->isValid();

  bool becameValid = (!oldUnitStatus && newUnitStatus);

  auto dataAccessFactory = _connection->dataAccessFactory();
  auto unitAccess        = dataAccessFactory->unitAccess();

  // not yet in the DB
  if (!unitEntry->getPersisted()) {
    if (becameValid) {
      beginResetModel();
      {
        unitAccess->insert(unitEntry->unit());

        unitEntry->setPersisted(true);

        // we add one more empty trait
        _unitEntries.append(new UnitTableEntry());
      }
      endResetModel();
    }
  } else if (newUnitStatus) // it was persisted and stays valid

    unitAccess->update(unitEntry->unit());

  return true;
}


QModelIndex
UnitModel::
parent(const QModelIndex& index) const
{
  Q_UNUSED(index);
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

  if (index.column() != UnitTableEntry::CloseAction)
    flags |= Qt::ItemIsEditable;

  flags ^= Qt::ItemIsSelectable;

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
  _connection = connection;

  reloadUnits();
}


void
UnitModel::
onClicked(const QModelIndex& index)
{
  if (!index.parent().isValid() &&
      index.column() == UnitTableEntry::CloseAction &&
      index.row() != _unitEntries.size() - 1) {
    auto unitEntry = _unitEntries[(index.row())];

    unitEntry->switchState();

    int  row = index.row();
    emit dataChanged(this->index(UnitTableEntry::Name, row),
                     this->index(UnitTableEntry::CloseAction, row));
  }
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

    QVector<Unit::Shared> units = unitAccess->findAll();

    for (Unit::Shared t : units)
      _unitEntries.append(new UnitTableEntry(t));

    // we add one more emptyunit
    Unit::Shared emptyUnit(new Unit());

    _unitEntries.append(new UnitTableEntry(emptyUnit));
  }
  endResetModel();
  //
}


void
UnitModel::
deleteMarkedEntries()
{
  if (_connection.isNull())
    return;

  auto dataAccessFactory = _connection->dataAccessFactory();

  auto unitAccess = dataAccessFactory->unitAccess();

  for (UnitTableEntry* entry : _unitEntries)
    if (entry->getPersisted() &&
        entry->getState() == UnitTableEntry::Deleted)
      unitAccess->remove(entry->unit());

}
