#ifndef Geo_Database_Private_ConnectionListModel_hpp
#define Geo_Database_Private_ConnectionListModel_hpp

#include <ConnectionListModel.hpp>

#include <QAbstractListModel>
#include <QSignalMapper>

#include <QQmlEngine>

#include <functional>

namespace Geo {
namespace Database {
namespace Private {
class ConnectionListModel : public QAbstractListModel,
                            public Geo::Database::ConnectionListModel {
  Q_OBJECT
  Q_DISABLE_COPY(ConnectionListModel)

private:
  typedef   Geo::Database::ConnectionListModel Base;

public:
  typedef typename Base::ConnectionList ConnectionList;
  typedef typename Base::ConstIterator  ConstIterator;

public:
  Q_INVOKABLE
  ConnectionListModel(QObject* parent = 0);

  ~ConnectionListModel();

  // QAbstractListModel Interface
  int
  rowCount(const QModelIndex& parent = QModelIndex()) const;

  QVariant
  data(const QModelIndex& index, int role = Qt::DisplayRole) const;

  bool
  setData(const QModelIndex& index, const QVariant& value, int role);
  // END QAbstractListModel Interface

  // Geo::Database::ConnectionListModel Interface
  Q_INVOKABLE
  ConstIterator
  begin() const { return ConstIterator(_connections.begin()); }

  Q_INVOKABLE
  ConstIterator
  end() const { return ConstIterator(_connections.end()); }
  // END Geo::Database::ConnectionListModel Interface

  Q_INVOKABLE bool
  insertRows(int const&         type,
             int const&         row,
             int const&         count,
             const QModelIndex& parent = QModelIndex());

  Q_INVOKABLE bool
  removeRows(int row, int count,
             const QModelIndex& parent = QModelIndex());

private slots:
  void
  updateObject(QObject* object);

private:
  void
  connectObject(QObject* object);

private:
  std::function<QObject*(int const&)> _objectFctory;
  QSignalMapper*                     _signaleMap;
  QObjectList                        _connections;
};
}
}
}
#endif
