#ifndef Geo_Database_TraitsWidgetModel_hpp
#define Geo_Database_TraitsWidgetModel_hpp

#include <Connections/Connection.hpp>
#include <Mixin/ConnectionAcceptor.hpp>

#include <QtCore/QAbstractItemModel>
#include <QtCore/QVariant>
#include <QtCore/QVector>

using Geo::Database::Connections::Connection;

namespace Geo {
namespace Database {
namespace Models {
namespace Traits {
//

class WellTraitEntry;

//

class TraitsWidgetModel:
  public QAbstractItemModel,
  public Database::Mixin::ConnectionAcceptor
{
  Q_OBJECT

public:
  TraitsWidgetModel();

  virtual
  ~TraitsWidgetModel();

public:
  virtual QVariant
  data(const QModelIndex& index, int role) const override;

  bool
  setData(const QModelIndex& index,
          const QVariant&    value,
          int                role = Qt::EditRole) override;

  virtual QModelIndex
  index(int row, int column, const QModelIndex& parent =
          QModelIndex()) const override;

  virtual QModelIndex
  parent(const QModelIndex& index) const override;

  virtual int
  columnCount(const QModelIndex& parent) const override;

  virtual int
  rowCount(const QModelIndex& parent) const override;

  QVariant
  headerData(int             section,
             Qt::Orientation orientation,
             int             role = Qt::DisplayRole) const override;

  Qt::ItemFlags
  flags(const QModelIndex& index) const override;

public slots:
  void
  setConnection(Database::Connections::Connection::Shared connection) override;

  void
  onClicked(const QModelIndex& index);

private:
  void
  reloadTraits();

  void
  saveTraits();

private:
  // database traits
  Connections::Connection::Shared _connection;

  QVector<WellTraitEntry*> _entries;
};

//
}
}
}
}

#endif //  Geo_Database_TraitsWidgetModel_hpp
