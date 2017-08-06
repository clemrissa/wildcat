#pragma once

#include <QtCore/QAbstractItemModel>

#include <Database/Connections/IConnection>

#include "Las/LasFile.hpp"

namespace Geo
{

using Database::IConnection;

namespace Import
{
namespace TreeWrapper
{
class TreeEntry;
class LasFileEntry;
}

class ImportTreeModel : public QAbstractItemModel
{
public:
  ImportTreeModel(std::vector<std::shared_ptr<LasFile> > lasFiles);

  ~ImportTreeModel();

public:

  std::vector<std::unique_ptr<TreeWrapper::TreeEntry>> const &
  getLasFileEntries() const;

  void
  setConnection(std::shared_ptr<IConnection> connection);

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

  std::vector<std::unique_ptr<TreeWrapper::TreeEntry>> _lasFileEntries;
  std::vector<std::shared_ptr<LasFile> > _lasFiles;

  std::shared_ptr<IConnection> _connection;

  int
  getEntryPosition(TreeWrapper::TreeEntry* const entry) const;
};

//
}
}
