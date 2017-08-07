#pragma once

#include <vector>
#include <memory>

#include <QtCore/QAbstractItemModel>

namespace Geo
{
namespace Database
{
namespace Gui
{

class ExplorerEntry;

class ExplorerTreeModel final : public QAbstractItemModel
{

  Q_OBJECT

public:

  ExplorerTreeModel();

  ~ExplorerTreeModel();

public:

  virtual
  QVariant
  data(const QModelIndex& index, int role) const override;

  virtual
  QModelIndex
  index(int row, int column, const QModelIndex& parent) const override;

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

private:

  int
  getEntryPosition(ExplorerEntry const * entry) const;

private:

  std::vector<std::unique_ptr<ExplorerEntry> > _explorerEntries;
};

//
}
}
}
