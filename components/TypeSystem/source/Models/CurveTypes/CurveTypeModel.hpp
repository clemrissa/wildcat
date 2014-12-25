#ifndef Geo_TypeSystem_Models_CurveTypeModel_hpp
#define Geo_TypeSystem_Models_CurveTypeModel_hpp

#include <QtCore/QAbstractItemModel>
#include <QtCore/QVector>

#include <Database/Connections/Connection>
#include <Database/Mixin/ConnectionAcceptor>

namespace Geo {
namespace TypeSystem {
namespace Models {
namespace CurveTypes {
//

class TreeEntry;
class FamilyEntry;
//

class CurveTypeModel:
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
  void
  loadXml(QString fileName);

  void
  saveXml(QString fileName);

  void
  setConnection(Database::Connections::Connection::Shared connection)
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
  reloadCurveTypes();

  FamilyEntry*
  getCachedFamilyEntry(QString familyName);

private:
  Database::Connections::Connection::Shared _connection;

  QVector<FamilyEntry*> _familyEntries;

  QMap<QString, FamilyEntry*> _familyEntryMap;
};

//
}
}
}
}
#endif // Geo_TypeSystem_Models_CurveTypeModel_hpp
