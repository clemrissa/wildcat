#ifndef Geo_TypeSystem_Models_UnitModel_hpp
#define Geo_TypeSystem_Models_UnitModel_hpp

#include <QtCore/QAbstractItemModel>
#include <QtCore/QPointer>
#include <QtCore/QVector>

#include <Database/Connections/Connection>
#include <Database/Mixin/ConnectionAcceptor>

namespace Geo {
namespace TypeSystem {
namespace Models {
namespace Units {
//

class UnitTableEntry;
//

class UnitModel:
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
          int                role = Qt::EditRole) override;

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

  Qt::ItemFlags
  flags(const QModelIndex& index) const override;

public slots:
  // TODO: save to DB loaded from XML units
  void
  loadXml(QString fileName);

  void
  saveXml(QString fileName);

  void
  setConnection(Database::Connections::Connection::Shared connection) override;

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
                             QString         newName);

private:
  Database::Connections::Connection::Shared _connection;

  QPointer<UnitTableEntry> _emptyUnitEntryStack;

  QMap<QString, UnitTableEntry*> _unitEntriesCacheMap;

  QVector<UnitTableEntry*> _unitEntries;
};

//
}
}
}
}
#endif // Geo_TypeSystem_Models_UnitModel_hpp
