#include "ConnectionListModel.hpp"

#include "Connection.hpp"

#include "Auxiliary/ExecutionControl.hpp"

#include <QMetaProperty>
#include <QObject>
// --

using Geo::Database::Private::ConnectionListModel;

ConnectionListModel::
ConnectionListModel(QObject* parent)
  : QAbstractListModel(parent),
    _objectFctory([this] (int const& databaseType) {
                    Connection* connection = new Connection(this);
                    connection->databaseType(databaseType);

                    return static_cast<QObject*>(connection);
                  }
                  ),
    _signaleMap(new QSignalMapper(this)) {

  INFO << "ConnectionListModel is being created";

  Connection* connection1 = new Connection(this);
  connection1->databaseType(DatabaseType::SQLite);
  connection1->database("Data1.db");
  Connection* connection2 = new Connection(this);
  connection2->databaseType(DatabaseType::MySql);
  connection2->database("Data2.db");
  Connection* connection3 = new Connection(this);
  connection3->databaseType(DatabaseType::SQLite);
  connection3->database("Geo3.db");
  _connections.push_back(connection1);
  _connections.push_back(connection2);
  _connections.push_back(connection3);

  QObject::connect(_signaleMap, SIGNAL(mapped(QObject*)),
                   this, SLOT(updateObject(QObject*)));

  connectObject(connection1);
  connectObject(connection2);
  connectObject(connection3);
}

ConnectionListModel::
~ConnectionListModel() {
  INFO << "ConnectionListModel is being destroyed";
  qDeleteAll(_connections);
}

int
ConnectionListModel::
rowCount(const QModelIndex& parent) const {
  return _connections.size();
}

QVariant
ConnectionListModel::
data(const QModelIndex& index, int role) const {
  if (role == Qt::DisplayRole || role == Qt::EditRole) {
    return QVariant::fromValue(_connections[index.row()]);
  }

  return QVariant();
}

bool
ConnectionListModel::
setData(const QModelIndex& index, const QVariant& value, int role) {
  QObject* object = value.value<QObject*>();

  if (!object) {
    return false;
  }

  if (object == static_cast<QObject*>(_connections.at(index.row()))) {
    return true;
  }

  delete _connections.at(index.row());
  _connections[index.row()] = object;
  connectObject(object);
  emit dataChanged(index, index, QVector<int>(1, role));

  return true;
}

bool
ConnectionListModel::
insertRows(int const&         type,
           int const&         row,
           int const&         count,
           const QModelIndex& parent) {
  Q_UNUSED(parent);
  beginInsertRows(QModelIndex(), row, row + count - 1);

  for (int i = row; i < row + count; ++i) {
    QObject* object = _objectFctory(type);
    Q_ASSERT(object);
    _connections.insert(i, object);
    connectObject(object);
    QQmlEngine::setObjectOwnership(object, QQmlEngine::CppOwnership);
  }

  endInsertRows();

  return true;
}

bool
ConnectionListModel::
removeRows(int row, int count,
           const QModelIndex& parent) {
  Q_UNUSED(parent);
  beginRemoveRows(QModelIndex(), row, row + count - 1);

  while (count--) {
    delete _connections.takeAt(row);
  }

  endRemoveRows();

  return true;
}

void
ConnectionListModel::
updateObject(QObject* object) {
  const int row = _connections.indexOf(object);
  emit      dataChanged(index(row), index(row));
}

void
ConnectionListModel::
connectObject(QObject* object) {
  int const slotIndex = _signaleMap->metaObject()->indexOfSlot("map()");

  QMetaMethod const slotMetaMethod =
    _signaleMap->metaObject()->method(slotIndex);
  int const props = object->metaObject()->propertyCount();

  for (int i = 0; i < props; ++i) {
    const QMetaProperty prop = object->metaObject()->property(i);

    if (prop.hasNotifySignal()) {
      QObject::connect(object, prop.notifySignal(),
                       _signaleMap, slotMetaMethod);
    }
  }
}
