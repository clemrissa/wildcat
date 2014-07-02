#include "ImportTreeModel.hpp"

#include <Uni/Logging/Logging>

#include "Las/LasFile.hpp"
#include "Las/TreeWrapper/LasFileEntry.hpp"
#include "Las/TreeWrapper/TreeEntry.hpp"

#include <QSharedPointer>

#include <algorithm>

using Geo::Import::ImportTreeModel;
using Geo::Import::TreeWrapper::LasFileEntry;
using Geo::Import::TreeWrapper::TreeEntry;

ImportTreeModel::
ImportTreeModel(QVector<LasFileEntry*> lasFileEntries):
  _lasFileEntries(lasFileEntries)
{
  //
}


ImportTreeModel::
ImportTreeModel(QVector<QSharedPointer<LasFile> > lasFiles)
{
  for (QSharedPointer<LasFile> lasFile : lasFiles)
    _lasFileEntries.append(new LasFileEntry(lasFile));
}


ImportTreeModel::
~ImportTreeModel()
{
  for (LasFileEntry* entry : _lasFileEntries)
    delete entry;
}


// -------------------------------------------

QVector<LasFileEntry*> const
ImportTreeModel::
getLasFileEntries() const
{
  return _lasFileEntries;
}


void
ImportTreeModel::
setConnection(Geo::Database::Connections::Connection::Shared connection)
{
  _connection = connection;

  for (TreeWrapper::TreeEntry* e : _lasFileEntries)
    e->setConnection(connection);
}


// --------------------------------------------

QVariant
ImportTreeModel::
data(const QModelIndex& index, int role) const
{
  if (!index.isValid())
    return QVariant();

  TreeEntry* entry =
    static_cast<TreeEntry*>(index.internalPointer());

  return entry->data(role, index.column());
}


QModelIndex
ImportTreeModel::
index(int row, int column, const QModelIndex& parent) const
{
  if (!parent.isValid())
    return QAbstractItemModel::createIndex(row, column, _lasFileEntries[row]);

  TreeEntry* entry =
    static_cast<TreeEntry*>(parent.internalPointer());

  if (entry->entries().size() == 0)
    return QModelIndex();

  return QAbstractItemModel::createIndex(row, column, entry->entries()[row]);
}


QModelIndex
ImportTreeModel::
parent(const QModelIndex& index) const
{
  TreeEntry* entry =
    static_cast<TreeEntry*>(index.internalPointer());

  Q_ASSERT(entry);

  TreeEntry* parentEntry = entry->parent();

  if (parentEntry == nullptr)
    return QModelIndex();

  TreeEntry* parentParentEntry = parentEntry->parent();

  int position = 0;

  if (parentParentEntry == nullptr)
    position = getEntryPosition(parentEntry);
  else
    position = parentParentEntry->positionOfChildEntry(parentEntry);

  return QAbstractItemModel::createIndex(position, 0, parentEntry);
}


int
ImportTreeModel::
columnCount(const QModelIndex& parent) const
{
  return TreeEntry::Column::Size;
}


int
ImportTreeModel::
rowCount(const QModelIndex& parent) const
{
  if (!parent.isValid())
    return _lasFileEntries.size();

  TreeEntry* entry =
    static_cast<TreeEntry*>(parent.internalPointer());

  return entry->entries().size();
}


QVariant
ImportTreeModel::
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
  case TreeEntry::Name:
    result = tr("Item");
    break;

  case TreeEntry::Description:
    result = tr("Description");
    break;

  case TreeEntry::Value:
    result = tr("Parsed Value");
    break;

  case TreeEntry::ImportValue:
    result = tr("Import Value");
    break;

  case TreeEntry::Type:
    result = tr("Type");
    break;

  case TreeEntry::Units:
    result = tr("Parsed Units");
    break;

  case TreeEntry::ImportUnits:
    result = tr("Import Units As");
    break;
  }

  return result;
}


Qt::ItemFlags
ImportTreeModel::
flags(const QModelIndex& index) const
{
  Qt::ItemFlags flags =   QAbstractItemModel::flags(index);

  flags |= Qt::ItemIsEditable;

  // flags ^= Qt::ItemIsSelectable;

  return flags;
}


int
ImportTreeModel::
getEntryPosition(TreeWrapper::TreeEntry* const entry) const
{
  auto it = std::find(_lasFileEntries.begin(),
                      _lasFileEntries.end(), entry);

  return it - _lasFileEntries.begin();
  //
}
