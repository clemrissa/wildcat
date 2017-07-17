#pragma once

#include <QtCore/QAbstractItemModel>

#include <Database/Connections/Connection>
#include <Database/Mixin/ConnectionAcceptor>

#include <vector>
#include <memory>

namespace Geo
{
namespace TypeSystem
{
namespace Models
{
namespace CurveTypes
{
//

class TreeEntry;
class FamilyEntry;
//

class CurveTypeModel :
  public QAbstractItemModel,
  public Database::Mixin::ConnectionAcceptor
{
  Q_OBJECT

public:
  CurveTypeModel();

  virtual
  ~CurveTypeModel();

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
  // TODO: save to DB loaded from XML curves

  void
  loadXml(QString fileName);

  void
  saveXml(QString fileName);

  void
  setConnection(Database::Connection::Shared connection)
  override;

  void
  onClicked(const QModelIndex& index);

private:
  int
  getEntryPosition(TreeEntry* const entry) const;

  bool
  setDataToCurveNode(const QModelIndex& index,
                     const QVariant&    value);

  bool
  setDataToFamilyNode(const QModelIndex& index,
                      const QVariant&    value);

  void
  updateCacheWithNewFamilyName(FamilyEntry* fe,
                               QString newFamilyName);

  void
  reloadCurveTypes();

  void
  deleteMarkedEntries();

  FamilyEntry*
  getCachedFamilyEntry(QString familyName);

  void
  pushEmptyFamilyEntry();

  void
  popEmptyFamilyEntry();

private:
  Database::Connection::Shared _connection;

  std::vector<FamilyEntry*> _familyEntries;

  QMap<QString, FamilyEntry*> _familyEntryCacheMap;

  std::unique_ptr<FamilyEntry> _emptyFamilyEntryStack;
};

//
}
}
}
}
