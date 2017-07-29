#pragma once

#include <QtCore/QAbstractItemModel>

#include <Database/Connections/IConnection>
#include <Database/Mixin/ConnectionAcceptor>

#include <vector>
#include <memory>

namespace Geo
{

using Database::IConnection;

namespace TypeSystem
{
namespace Gui
{
namespace Units
{
//

class UnitTableEntry;
//

class UnitModel :
  public QAbstractItemModel,
  public Database::Mixin::ConnectionAcceptor
{
  Q_OBJECT

public:
  UnitModel();

  virtual
  ~UnitModel();

  virtual
  QVariant
  data(const QModelIndex& index, int role) const override;

  virtual
  QModelIndex
  index(int row, int column, const QModelIndex& parent =
          QModelIndex()) const override;

  bool
  setData(const QModelIndex& index,
          const QVariant&    value,
          int role = Qt::EditRole) override;

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
  headerData(int section,
             Qt::Orientation orientation,
             int role = Qt::DisplayRole) const override;

  Qt::ItemFlags
  flags(const QModelIndex& index) const override;

public slots:
  //
  // TODO: save to DB loaded from XML units
  void
  loadXml(QString fileName);

  void
  saveXml(QString fileName);

  void
  setConnection(std::shared_ptr<IConnection> connection) override;

  void
  onClicked(const QModelIndex& index);

private:
  int
  getEntryPosition(UnitTableEntry* const entry) const;

  void
  reloadUnits();

  void
  deleteMarkedEntries();

  void
  pushEmptyUnitEntry();

  void
  popEmptyUnitEntry();

  UnitTableEntry*
  getCachedUnitEntry(QString familyName);

  void
  updateCacheWithNewUnitName(UnitTableEntry* unitEntry,
                             QString newName);

private:

  std::shared_ptr<IConnection> _connection;

  std::unique_ptr<UnitTableEntry> _emptyUnitEntryStack;

  QMap<QString, UnitTableEntry*> _unitEntriesCacheMap;

  std::vector<UnitTableEntry*> _unitEntries;
};

//
}
}
}
}
