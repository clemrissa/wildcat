#pragma once

#include <vector>
#include <memory>

#include <QtCore/QAbstractItemModel>
#include <QtCore/QVariant>

#include <Connections/IConnection.hpp>
#include <Connections/DatabaseType.hpp>

namespace Geo
{
namespace Database
{
class ConnectionManager;

namespace Gui
{

class Entry;

class ConnectionsEditorWidgetModel : public QAbstractItemModel
{
  Q_OBJECT

public:
  ConnectionsEditorWidgetModel();

  virtual
  ~ConnectionsEditorWidgetModel();

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

  QVariant
  headerData(int section,
             Qt::Orientation orientation,
             int role = Qt::DisplayRole) const override;

  Qt::ItemFlags
  flags(const QModelIndex& index) const override;

public slots:

  void
  addConnection(DatabaseType databaseType);

  /// Currently processes clicks on "Remove Connection" table column
  void
  onClicked(const QModelIndex& index);

private:
  ConnectionManager* _connectionsManager;

  std::vector<std::unique_ptr<Entry> > _entries;

  //int
  //getEntryPosition(Entry* entry) const;
};

//
}
}
}
