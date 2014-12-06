#ifndef Geo_TypeSystem_Models_UnitModel_hpp
#define Geo_TypeSystem_Models_UnitModel_hpp

#include <QtCore/QAbstractItemModel>
#include <QtCore/QVector>

#include <Database/Connections/Connection>
#include <Database/Mixin/ConnectionAcceptor>

namespace Geo {
namespace TypeSystem {
namespace Models {
namespace Units {
//

class TreeEntry;
//

class UnitModel:
  public QAbstractItemModel,
  public Database::Mixin::ConnectionAcceptor
{
public:
  UnitModel();

  virtual
  ~UnitModel();

  virtual
  QVariant
  data(const QModelIndex& index, int role) const override;

  virtual
  QModelIndex
  index(int row, int column, const QModelIndex& parent) const override;

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
  setConnection(Database::Connections::Connection::Shared connection) override;

private:
  int
  getEntryPosition(TreeEntry* const entry) const;

private:
  QVector<TreeEntry*> _units;
};

//
}
}
}
}
#endif // Geo_TypeSystem_Models_UnitModel_hpp
