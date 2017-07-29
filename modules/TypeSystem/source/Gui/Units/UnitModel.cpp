#include "UnitModel.hpp"

#include <QtCore/QFile>
#include <QtCore/QTextStream>

#include "UnitTableEntry.hpp"

#include <Domain/Unit>

using Geo::TypeSystem::Gui::Units::UnitModel;
using Geo::TypeSystem::Gui::Units::UnitTableEntry;

UnitModel::
UnitModel()
{
  reloadUnits();
}


UnitModel::
~UnitModel()
{
  // remove from DB
  deleteMarkedEntries();

  // clear container
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
        int role)
{
  using Geo::Domain::Unit;

  if (role != Qt::EditRole)
    return false;

  auto unitEntry =
    static_cast<UnitTableEntry*>(index.internalPointer());

  bool oldUnitStatus = unitEntry->unit()->isValid();

  switch (index.column())
  {
    case UnitTableEntry::Name:

      updateCacheWithNewUnitName(unitEntry, value.toString());

      unitEntry->unit()->setName(value.toString());
      break;

    case UnitTableEntry::Symbol:
      unitEntry->unit()->setSymbol(value.toString());
      break;

    case UnitTableEntry::Scale:
    {
      bool ok;
      unitEntry->unit()->setScale(value.toDouble(&ok));
      break;
    }

    case UnitTableEntry::Offset:
    {
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

  if (!_connection)
    return false;

  auto dataAccessFactory = _connection->dataAccessFactory();
  auto unitAccess = dataAccessFactory->unitAccess();

  // not yet in the DB
  if (!unitEntry->getPersisted())
  {
    if (becameValid)
    {
      beginInsertRows(index.parent(), index.row(), index.row());;
      {
        unitAccess->insert(unitEntry->unit());

        unitEntry->setPersisted(true);

        // we add one more empty trait
        getCachedUnitEntry(QString());
      }
      endInsertRows();
    }
  }
  else if (newUnitStatus)   // it was persisted and stays valid

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
headerData(int section,
           Qt::Orientation orientation,
           int role)  const
{
  QVariant result;

  if (role != Qt::DisplayRole)
    return result;

  if (orientation == Qt::Vertical)
    return result;

  result = UnitTableEntry::headerData(section);

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
  QDomDocument doc("Units");

  QFile file(fileName);

  if (!file.open(QIODevice::ReadOnly))
    return;

  if (!doc.setContent(&file))
  {
    file.close();
    return;
  }

  file.close();

  //// ------

  beginResetModel();
  {
    pushEmptyUnitEntry();

    QDomElement docElem = doc.documentElement();

    auto e = docElem.firstChildElement("CurveType");

    while (!e.isNull())
    {
      // add cache here

      auto name = e.firstChildElement("Name").text();

      auto unitEntry = getCachedUnitEntry(name);

      unitEntry->addXmlData(e);

      e = e.nextSiblingElement("CurveType");
    }

    popEmptyUnitEntry();
  }
  endResetModel();

  // set current DB connection to newly added nodes
  for (auto e : _unitEntries)
    e->setConnection(_connection);
}


void
UnitModel::
saveXml(QString fileName)
{
  QDomDocument doc("Units");

  QDomElement root = doc.createElement("Units");

  doc.appendChild(root);

  for (auto e : _unitEntries)
    if (e->unit())
      root.appendChild(e->getXmlDescription(doc));

  // -

  QFile file(fileName);

  if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    return;

  QTextStream out(&file);

  out << doc.toString();
}


void
UnitModel::
setConnection(std::shared_ptr<IConnection> connection)
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
      (unsigned)index.row() != _unitEntries.size() - 1)
  {
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
}


void
UnitModel::
reloadUnits()
{
  if (!_connection)
    return;

  beginResetModel();
  {
    qDeleteAll(_unitEntries);
    _unitEntries.resize(0);

    using Geo::Domain::Unit;

    auto dataAccessFactory = _connection->dataAccessFactory();

    auto unitAccess = dataAccessFactory->unitAccess();

    std::vector<Unit::Shared> units = unitAccess->findAll();

    for (Unit::Shared t : units)
    {
      QString unitName = t->getName();

      _unitEntriesCacheMap.remove(unitName);

      auto unitEntry = new UnitTableEntry(t);

      _unitEntriesCacheMap[unitName] = unitEntry;
      _unitEntries.push_back(unitEntry);
    }

    // we add one more emptyunit
    Unit::Shared emptyUnit(new Unit());

    _unitEntries.push_back(new UnitTableEntry(emptyUnit));
  }
  endResetModel();
  //
}


void
UnitModel::
deleteMarkedEntries()
{
  if (!_connection)
    return;

  auto dataAccessFactory = _connection->dataAccessFactory();

  auto unitAccess = dataAccessFactory->unitAccess();

  for (UnitTableEntry* entry : _unitEntries)
    if (entry->getPersisted() &&
        entry->getState() == UnitTableEntry::Deleted)
      unitAccess->remove(entry->unit());
}


void
UnitModel::
pushEmptyUnitEntry()
{
  if (_unitEntries.size() &&
      !_unitEntries.back()->unit()->isValid())
  {
    Q_ASSERT(!_emptyUnitEntryStack);

    _emptyUnitEntryStack.reset(_unitEntries.back());

    _unitEntries.erase(_unitEntries.end() - 1);
  }
}


void
UnitModel::
popEmptyUnitEntry()
{
  if (_emptyUnitEntryStack)
  {
    _unitEntries.push_back(_emptyUnitEntryStack.release());
  }
}


UnitTableEntry*
UnitModel::
getCachedUnitEntry(QString unitName)
{
  UnitTableEntry* result = nullptr;

  if (_unitEntriesCacheMap.contains(unitName))
    result = _unitEntriesCacheMap[unitName];

  else
  {
    result = new UnitTableEntry();

    _unitEntriesCacheMap[unitName] = result;

    _unitEntries.push_back(result);
  }

  return result;
}


void
UnitModel::
updateCacheWithNewUnitName(UnitTableEntry* unitEntry,
                           QString newName)
{
  _unitEntriesCacheMap.remove(unitEntry->unit()->getName());
  _unitEntriesCacheMap[newName] = unitEntry;
}
