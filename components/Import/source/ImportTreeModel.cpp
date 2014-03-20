#include "ImportTreeModel.hpp"

#include <Uni/Logging/Logging>

#include "Las/ImportTreeWrapperEntry.hpp"
#include "Las/ImportTreeWrapperLasFile.hpp"
#include "Las/LasFile.hpp"

#include <QSharedPointer>

#include <algorithm>

namespace Geo {
namespace Import {
ImportTreeModel::
ImportTreeModel(QVector<ImportTreeWrapperLasFile*> importTreeWrapperLasFiles):
  _importTreeWrapperLasFiles(importTreeWrapperLasFiles) {
  //
}

QVariant
ImportTreeModel::
data(const QModelIndex& index, int role) const  {
  if (!index.isValid())
    return QVariant();

  if (role != Qt::DisplayRole)
    return QVariant();

  ImportTreeWrapperEntry* entry =
    static_cast<ImportTreeWrapperEntry*>(index.internalPointer());

  return entry->data(role, index.column());
}

QModelIndex
ImportTreeModel::
index(int row, int column, const QModelIndex& parent) const  {
  if (!parent.isValid())
    return QAbstractItemModel::createIndex(row, column, _importTreeWrapperLasFiles[row]);

  ImportTreeWrapperEntry* entry =
    static_cast<ImportTreeWrapperEntry*>(parent.internalPointer());

  if (entry->entries().size() == 0)
    return QModelIndex();

  return QAbstractItemModel::createIndex(row, column, entry->entries()[row]);
}

QModelIndex
ImportTreeModel::
parent(const QModelIndex& index) const  {
  ImportTreeWrapperEntry* entry =
    static_cast<ImportTreeWrapperEntry*>(index.internalPointer());

  Q_ASSERT(entry);

  ImportTreeWrapperEntry* parentEntry = entry->parent();

  if (parentEntry == nullptr)
    return QModelIndex();

  ImportTreeWrapperEntry* parentParentEntry = parentEntry->parent();

  int position = 0;

  if (parentParentEntry == nullptr)
    position = getEntryPosition(parentEntry);
  else
    position = parentParentEntry->positionOfChildEntry(parentEntry);

  return QAbstractItemModel::createIndex(position, 0, parentEntry);
}

int
ImportTreeModel::
columnCount(const QModelIndex& parent) const  {
  // it does not matter as this model is a "fake" one
  // the true number of columns is returned my main model attached
  // to a view
  //return 6;
  return ImportTreeWrapperEntry::Column::Size;
}

int
ImportTreeModel::
rowCount(const QModelIndex& parent) const {
  if (!parent.isValid())
    return _importTreeWrapperLasFiles.size();

  ImportTreeWrapperEntry* entry =
    static_cast<ImportTreeWrapperEntry*>(parent.internalPointer());

  return entry->entries().size();
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
  case ImportTreeWrapperEntry::Name:
    result = tr("Item");
    break;

  case ImportTreeWrapperEntry::Description:
    result = tr("Description");
    break;

  case ImportTreeWrapperEntry::Value:
    result = tr("Value");
    break;

  case ImportTreeWrapperEntry::ImportName:
    result = tr("Import As");
    break;

  case ImportTreeWrapperEntry::Type:
    result = tr("Type");
    break;

  case ImportTreeWrapperEntry::Units:
    result = tr("Parsed Units");
    break;

  case ImportTreeWrapperEntry::ImportUnits:
    result = tr("Import Units As");
    break;
  }

  return result;
}

int
ImportTreeModel::
getEntryPosition(ImportTreeWrapperEntry* const entry) const {
  auto it = std::find(_importTreeWrapperLasFiles.begin(),
                      _importTreeWrapperLasFiles.end(), entry);

  return it - _importTreeWrapperLasFiles.begin();
  //
}
}
}
