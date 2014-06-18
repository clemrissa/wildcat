#ifndef Geo_Database_ConnectionsWidgetModel_hpp
#define Geo_Database_ConnectionsWidgetModel_hpp

#include <QAbstractItemModel>
#include <QVariant>
#include <QVector>

#include <Connections/Connection.hpp>

namespace Geo {
namespace Database {
namespace Connections {
class ConnectionManager;
}

namespace Models {
namespace ConnectionsWidgetModel {
//

class Entry;

class ConnectionsWidgetModel: public QAbstractItemModel {
  Q_OBJECT

public:
  // TODO implement
  ConnectionsWidgetModel();

  virtual
  ~ConnectionsWidgetModel();

public:
  virtual
  QVariant
  data(const QModelIndex& index, int role) const override;

  virtual
  QModelIndex
  index(int row, int column, const QModelIndex& parent) const override;

  virtual
  QModelIndex
  parent(const QModelIndex& index) const override;

  virtual
  int
  columnCount(const QModelIndex& parent) const override;

  virtual
  int
  rowCount(const QModelIndex& parent) const override;

  //

  // bool
  // insertRows(int row, int count, const QModelIndex & parent = QModelIndex())
  // override;

  //

  QVariant
  headerData(int             section,
             Qt::Orientation orientation,
             int             role = Qt::DisplayRole) const override;

  Qt::ItemFlags
  flags(const QModelIndex& index) const override;

public slots:
  void
  addConnection(Connections::DatabaseType databaseType);

  void
  onClicked(const QModelIndex& index);

private:
  Connections::ConnectionManager* _connectionsManager;

  QVector<Entry*> _entries;

  int
  getEntryPosition(Entry* entry) const;
};
}
}
}
}

#endif //  Geo_Database_ConnectionsWidgetModel_hpp
