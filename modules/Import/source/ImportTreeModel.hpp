#pragma once

#include <QtCore/QAbstractItemModel>

#include <Database/Connections/Connection>

#include "Las/LasFile.hpp"

namespace Geo {
namespace Import {
namespace TreeWrapper {
class TreeEntry;
class LasFileEntry;
}

class ImportTreeModel : public QAbstractItemModel
{
public:
  ImportTreeModel(std::vector<LasFile::Shared> lasFiles);

  ~ImportTreeModel();

public:
  std::vector<TreeWrapper::LasFileEntry*> const
  getLasFileEntries() const;

  void
  setConnection(Geo::Database::Connection::Shared connection);

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
  std::vector<TreeWrapper::LasFileEntry*> _lasFileEntries;
  std::vector<LasFile::Shared> _lasFiles;

  Geo::Database::Connection::Shared _connection;

  int
  getEntryPosition(TreeWrapper::TreeEntry* const entry) const;
};
}
}
