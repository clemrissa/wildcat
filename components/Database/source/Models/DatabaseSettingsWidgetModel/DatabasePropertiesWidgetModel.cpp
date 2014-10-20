#include "DatabasePropertiesWidgetModel.hpp"

#include "WellTraitEntry.hpp"

#include <Uni/Logging/Logging>

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
  saveTraits();

  qDeleteAll(_entries);
}


QVariant
DatabasePropertiesWidgetModel::
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
    auto list = value.toString().split(",", QString::SkipEmptyParts);

    for (QString& s : list)
      s = s.toUpper();

    traitEntry->trait()->setSynonyms(list);

    break;
  }

  case WellTraitEntry::Type: {
    using Geo::Domain::WellTrait;

    traitEntry->trait()->setType(static_cast<WellTrait::Type>(value.toInt()));

    break;
  }
  }

  bool newTraitStatus = traitEntry->trait()->isValid();

  // if a trait became valid
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

  saveTraits();

  emit dataChanged(index, index);

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

  return WellTraitEntry::Size;
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
onClicked(const QModelIndex& index)
{
  if (!index.parent().isValid() &&
      index.column() == WellTraitEntry::CloseAction &&
      index.row() != _entries.size() - 1) {
    beginRemoveRows(QModelIndex(), index.row(), index.row());

    auto connectionWrapper = _entries.takeAt(index.row());
    delete connectionWrapper;

    endRemoveRows();
  }
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

  int counter = 0;

  for (WellTraitEntry* e : _entries) {
    bool valid = e->trait()->isValid();

    // if (e->trait()->isValid())
    if (valid)
      wellTraitAccess->insert(e->trait());

    counter++;
  }
}
