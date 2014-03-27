#ifndef Geo_Database_DatabaseSettingsTreeModel_hpp
#define Geo_Database_DatabaseSettingsTreeModel_hpp

#include <QAbstractItemModel>
#include <QVariant>

// #include "ConnectionsManager.hpp"

// #include <QStandartPaths>

namespace Geo {
namespace Database {
class ConnectionsManager;
class DatabaseSettingsTreeEntry;

class DatabaseSettingsTreeModel: public QAbstractItemModel {
public:
  // TODO implement
  DatabaseSettingsTreeModel();

  virtual
  ~DatabaseSettingsTreeModel();

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

  bool
  insertRows(int row, int count, const QModelIndex & parent = QModelIndex()) override;

  //

  QVariant
  headerData(int             section,
             Qt::Orientation orientation,
             int             role = Qt::DisplayRole) const override;

  Qt::ItemFlags 
  flags(const QModelIndex &index) const override;

public slots:
  void
  addConnection(int index);

private:
  ConnectionsManager* _connectionsManager;

  std::vector<DatabaseSettingsTreeEntry*> _entries;

  int
  getEntryPosition(DatabaseSettingsTreeEntry* entry) const;
};
}
}

#endif //  Geo_Database_DatabaseSettingsTreeModel_hpp
