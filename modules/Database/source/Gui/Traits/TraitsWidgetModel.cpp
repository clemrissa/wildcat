#include "TraitsWidgetModel.hpp"

#include "WellTraitEntry.hpp"

using Geo::Database::Gui::TraitsWidgetModel;

TraitsWidgetModel::
TraitsWidgetModel()
{
  reloadTraits();
}


TraitsWidgetModel::
~TraitsWidgetModel()
{
  deleteMarkedEntries();
}


QVariant
TraitsWidgetModel::
data(const QModelIndex& index, int role) const
{
  Q_UNUSED(role);

  QVariant result;

  if (!index.isValid())
    return result;

  auto traitEntry =
    static_cast<WellTraitEntry*>(index.internalPointer());

  if (!traitEntry)
    return result;

  return traitEntry->data(role, index.column());
}


bool
TraitsWidgetModel::
setData(const QModelIndex& index,
        const QVariant&    value,
        int role)
{
  using Geo::Domain::WellTrait;

  if (role != Qt::EditRole)
    return false;

  auto traitEntry =
    static_cast<WellTraitEntry*>(index.internalPointer());

  bool oldTraitStatus = traitEntry->trait()->isValid();

  switch (index.column())
  {
    case WellTraitEntry::Trait:
    {
      traitEntry->trait()->setName(value.toString().toUpper());
      break;
    }

    case WellTraitEntry::Synonyms:
    {
      auto list = value.toString().split(",", QString::SkipEmptyParts);

      for (QString& s : list)
        s = s.toUpper();

      traitEntry->trait()->setSynonyms(list);

      break;
    }

    case WellTraitEntry::Type:
    {
      traitEntry->trait()->setType(static_cast<WellTrait::Type>(value.toInt()));

      break;
    }
  }

  bool newTraitStatus = traitEntry->trait()->isValid();
  bool becameValid    = (!oldTraitStatus && newTraitStatus);

  // if a trait became valid

  auto dataAccessFactory = _connection->dataAccessFactory();

  auto wellTraitAccess = dataAccessFactory->wellTraitAccess();

  // not yet in the DB
  if (!traitEntry->getPersisted())
  {
    if (becameValid)
    {
      beginResetModel();
      {
        wellTraitAccess->insert(traitEntry->trait());

        traitEntry->setPersisted(true);

        // we add one more empty trait
        WellTrait::Shared emptyTrait(new WellTrait());

        _entries.push_back(std::make_unique<WellTraitEntry>(emptyTrait));
      }
      endResetModel();
    }
  }
  else if (newTraitStatus)   // it was persisted and stays valid

    wellTraitAccess->update(traitEntry->trait());

  return true;
}


QModelIndex
TraitsWidgetModel::
index(int row, int column, const QModelIndex& parent) const
{
  Q_UNUSED(row);
  Q_UNUSED(column);

  if (!parent.isValid())
  {
    WellTraitEntry* entry = ((unsigned)row == _entries.size()) ?
                            nullptr :
                            _entries[row].get();

    return QAbstractItemModel::createIndex(row, column, entry);
  }

  return QModelIndex();
}


QModelIndex
TraitsWidgetModel::
parent(const QModelIndex& index) const
{
  Q_UNUSED(index);

  return QModelIndex();
}


int
TraitsWidgetModel::
columnCount(const QModelIndex& parent) const
{
  Q_UNUSED(parent);

  return WellTraitEntry::Size;
}


int
TraitsWidgetModel::
rowCount(const QModelIndex& parent) const
{
  Q_UNUSED(parent);
  return _entries.size();
}


QVariant
TraitsWidgetModel::
headerData(int section,
           Qt::Orientation orientation,
           int role)  const
{
  QVariant result;

  if (role != Qt::DisplayRole)
    return result;

  if (orientation == Qt::Vertical)
    return result;

  switch (section)
  {
    case WellTraitEntry::Trait:
      result = tr("Trait");
      break;

    case WellTraitEntry::Synonyms:
      result = tr("Synonyms");
      break;

    case WellTraitEntry::Type:
      result = tr("Data Type");
      break;

    default:
      result = QVariant();
      break;
  }

  return result;
}


Qt::ItemFlags
TraitsWidgetModel::
flags(const QModelIndex& index) const
{
  Qt::ItemFlags flags = QAbstractItemModel::flags(index);

  if (index.column() != WellTraitEntry::CloseAction)
    flags |= Qt::ItemIsEditable;

  flags ^= Qt::ItemIsSelectable;

  return flags;
}


void
TraitsWidgetModel::
setConnection(std::shared_ptr<IConnection> connection)
{
  _connection = connection;

  reloadTraits();
}


void
TraitsWidgetModel::
onClicked(const QModelIndex& index)
{
  if (!index.parent().isValid() &&
      index.column() == WellTraitEntry::CloseAction &&
      (unsigned)index.row() != _entries.size() - 1)
  {
    auto const & wellTraitEntry = _entries[index.row()];

    wellTraitEntry->switchState();

    int  row = index.row();
    emit dataChanged(this->index(WellTraitEntry::Trait, row),
                     this->index(WellTraitEntry::CloseAction, row));
  }
}


void
TraitsWidgetModel::
reloadTraits()
{
  if (!_connection)
    return;

  beginResetModel();
  {
    _entries.clear();

    using Geo::Domain::WellTrait;

    auto dataAccessFactory = _connection->dataAccessFactory();

    auto wellTraitAccess = dataAccessFactory->wellTraitAccess();

    std::vector<WellTrait::Shared> traits = wellTraitAccess->findAll();

    for (WellTrait::Shared t : traits)
      _entries.push_back(std::make_unique<WellTraitEntry>(t));

    // we add one more empty trait
    WellTrait::Shared emptyTrait(new WellTrait());

    _entries.push_back(std::make_unique<WellTraitEntry>(emptyTrait));
  }
  endResetModel();
}


void
TraitsWidgetModel::
deleteMarkedEntries()
{
  if (!_connection)
    return;

  auto dataAccessFactory = _connection->dataAccessFactory();

  auto wellTraitAccess = dataAccessFactory->wellTraitAccess();

  for (std::unique_ptr<WellTraitEntry> const & entry : _entries)
    if (entry->getPersisted() &&
        entry->getState() == WellTraitEntry::Deleted)
      wellTraitAccess->remove(entry->trait());
}
