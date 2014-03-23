#ifndef Geo_Database_DatabaseSettingsTreeModel_hpp
#define Geo_Database_DatabaseSettingsTreeModel_hpp

#include <QAbstractItemModel>
#include <QVariant>

// #include "ConnectionsManager.hpp"

// #include <QStandartPaths>

namespace Geo {
namespace Database {
class ConnectionsManager;

class DatabaseSettingsTreeModel: public QAbstractItemModel {
public:
  // TODO implement
  DatabaseSettingsTreeModel();

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

  QVariant
  headerData(int             section,
             Qt::Orientation orientation,
             int             role = Qt::DisplayRole) const override;

private:
  ConnectionsManager* _connectionsManager;
};
}
}

#endif //  Geo_Database_DatabaseSettingsTreeModel_hpp
