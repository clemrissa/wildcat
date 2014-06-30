#include "DatabasePropertiesWidgetModel.hpp"

#include "WellTraitEntry.hpp"

using Geo::Database::Models::DatabaseSettingsWidgetModel::
      DatabasePropertiesWidgetModel;

DatabasePropertiesWidgetModel::
DatabasePropertiesWidgetModel()
{
  reloadTraits();
}


DatabasePropertiesWidgetModel::
~DatabasePropertiesWidgetModel()
{
  qDeleteAll(_entries);
}


QVariant
DatabasePropertiesWidgetModel::
data(const QModelIndex& index, int role) const
{
  Q_UNUSED(role);

  if (!index.isValid())
    return QVariant();

  auto traitEntry =
    static_cast<WellTraitEntry*>(index.internalPointer());

  return traitEntry->data(role, index.column());
}


bool
DatabasePropertiesWidgetModel::
setData(const QModelIndex& index,
        const QVariant&    value,
        int                role)
{
  if (role != Qt::EditRole)
    return false;

  auto traitEntry =
    static_cast<WellTraitEntry*>(index.internalPointer());

  bool oldTraitStatus = traitEntry->trait()->isValid();

  switch (index.column()) {
  case WellTraitEntry::Trait: {
    traitEntry->trait()->setName(value.toString().toUpper());
    break;
  }

  case WellTraitEntry::Synonyms: {
    auto list =
      value.toString().split(",", QString::SkipEmptyParts);

    traitEntry->trait()->setSynonyms(list);

    break;
  }
  }

  bool newTraitStatus = traitEntry->trait()->isValid();

  emit dataChanged(index, index);

  if (!oldTraitStatus && newTraitStatus) {
    // add new data if necessary
    beginResetModel();
    {
      using Geo::Domain::WellTrait;

      // we add one more empty trait
      WellTrait::Shared emptyTrait(new WellTrait());

      _entries.append(new WellTraitEntry(emptyTrait));
    }
    endResetModel();
  }

  return true;
}


QModelIndex
DatabasePropertiesWidgetModel::
index(int row, int column, const QModelIndex& parent) const
{
  Q_UNUSED(row);
  Q_UNUSED(column);

  if (!parent.isValid()) {
    WellTraitEntry* entry =
      (row == _entries.size()) ? nullptr : _entries[row];

    return QAbstractItemModel::createIndex(row, column, entry);
  }

  return QModelIndex();
}


QModelIndex
DatabasePropertiesWidgetModel::
parent(const QModelIndex& index) const
{
  Q_UNUSED(index);

  return QModelIndex();
}


int
DatabasePropertiesWidgetModel::
columnCount(const QModelIndex& parent) const
{
  Q_UNUSED(parent);

  return 3;
}


int
DatabasePropertiesWidgetModel::
rowCount(const QModelIndex& parent) const
{
  Q_UNUSED(parent);
  return _entries.size();
}


QVariant
DatabasePropertiesWidgetModel::
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
  case WellTraitEntry::Trait:
    result = tr("Trait");
    break;

  case WellTraitEntry::Synonyms:
    result = tr("Synonyms");
    break;

  default:
    result = QVariant();
    break;
  }

  return result;
}


Qt::ItemFlags
DatabasePropertiesWidgetModel::
flags(const QModelIndex& index) const
{
  Qt::ItemFlags flags =   QAbstractItemModel::flags(index);

  if (index.column() != WellTraitEntry::CloseAction)
    flags |= Qt::ItemIsEditable;

  flags ^= Qt::ItemIsSelectable;

  return flags;
}


void
DatabasePropertiesWidgetModel::
setConnection(Connections::Connection::Shared connection)
{
  if (!_connection.isNull())
    saveTraits();

  _connection = connection;

  reloadTraits();
}


void
DatabasePropertiesWidgetModel::
reloadTraits()
{
  if (_connection.isNull())
    return;

  beginResetModel();
  {
    qDeleteAll(_entries);
    _entries.resize(0);

    using Geo::Domain::WellTrait;

    auto dataAccessFactory = _connection->dataAccessFactory();

    auto wellTraitAccess = dataAccessFactory->wellTraitAccess();

    QVector<WellTrait::Shared> traits = wellTraitAccess->findAll();

    for (WellTrait::Shared t : traits)
      _entries.append(new WellTraitEntry(t));

    // we add one more empty trait
    WellTrait::Shared emptyTrait(new WellTrait());

    _entries.append(new WellTraitEntry(emptyTrait));
  }
  endResetModel();
}


void
DatabasePropertiesWidgetModel::
saveTraits()
{
  using Geo::Domain::WellTrait;

  auto dataAccessFactory = _connection->dataAccessFactory();

  auto wellTraitAccess = dataAccessFactory->wellTraitAccess();

  QVector<WellTrait::Shared> traits = wellTraitAccess->findAll();

  for (WellTrait::Shared t : traits)
    wellTraitAccess->remove(t);

  for (WellTraitEntry* e : _entries)
    if (e->trait()->isValid())
      wellTraitAccess->insert(e->trait());

}
