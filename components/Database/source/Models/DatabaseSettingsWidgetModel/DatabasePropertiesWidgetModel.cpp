#include "DatabasePropertiesWidgetModel.hpp"


using Geo::Database::Models::DatabasePropertiesWidgetModel::DatabasePropertiesWidgetModel;


DatabasePropertiesWidgetModel::
DatabasePropertiesWidgetModel()
{

  //using Connections::ConnectionManager;
  //using DependencyManager::ApplicationContext;

  //_connectionsManager =
    //ApplicationContext::create<ConnectionManager>("Database.ConnectionManager");

  //for (auto connection : _connectionsManager->connections())
    //_entries.push_back(new ConnectionEntry(connection));

  //// last empty entry ( a placeholder for adding new connections )
  //_entries.push_back(new ConnectionEntry());

  //----------------

  //here we load traits from db
}



DatabasePropertiesWidgetModel::
~DatabasePropertiesWidgetModel()
{
//
}

QVariant
DatabasePropertiesWidgetModel::
data(const QModelIndex& index, int role) const
{
  if (!index.isValid())
    return QVariant();

  //Entry* entry =
    //static_cast<Entry*>(index.internalPointer());

  //return entry->data(role, index.column());
  return QVariant();
}

QModelIndex
DatabasePropertiesWidgetModel::
index(int row, int column, const QModelIndex& parent) const
{
  QModelIndex index;


  //if (!parent.isValid())
    //index =  QAbstractItemModel::createIndex(row, column, _entries[row]);

  return index;
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

  return 2;
}

int
DatabasePropertiesWidgetModel::
rowCount(const QModelIndex& parent) const
{
  //if (!parent.isValid())
    //return _connectionsManager->size();

  return 0;
}

QVariant
DatabasePropertiesWidgetModel::
headerData(int             section,
           Qt::Orientation orientation,
           int             role)  const
{
  QVariant result;


  //if (role != Qt::DisplayRole)
    //return result;

  //if (orientation == Qt::Vertical)
    //return result;

  //switch (section) {
  //case Entry::Type:
    //result = tr("Type");
    //break;

  //case Entry::Database:
    //result = tr("Database");
    //break;

  //default:
    //result = QVariant();
    //break;
  //}

  return result;
}

Qt::ItemFlags
DatabasePropertiesWidgetModel::
flags(const QModelIndex& index) const
{
  return QAbstractItemModel::flags(index);
}
