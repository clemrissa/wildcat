
#pragma once

#include <algorithm>
#include <vector>
#include <memory>

#include <QVariant>

#include <Las/LasFile.hpp>

#include <Database/Connections/IConnection>

class QAbstractItemModel;

namespace Geo
{

using Database::IConnection;

namespace Import
{
namespace TreeWrapper
{

/// @brief Composite pattern. Used to represent LAS file strurcture as a tree.
/// Every subclass works with sertain data from the LasFile class.
/// The whole tree is employed then in AbstractItemMoodel for QTreeView
class TreeEntry : public QObject
{
public:
  enum Column
  {
    Name        = 0,
    Description = 1,
    Value       = 2,
    ImportValue = 3,
    Type        = 4,
    Units       = 5,
    ImportUnits = 6,
    Size
  };

public:
  TreeEntry(std::shared_ptr<LasFile> lasFile,
            TreeEntry*      parent = nullptr) :
    _parent(parent),
    _lasFile(lasFile)
  {
    //
  }

  virtual
  ~TreeEntry() = default;

  TreeEntry*
  parent() { return _parent; }

  std::vector<std::unique_ptr<TreeEntry>> const &
  entries() const { return _entries; }

  int
  positionOfChildEntry(TreeEntry* const childEntry) const;

  std::shared_ptr<LasFile> const
  lasFile() const { return _lasFile; }

  std::shared_ptr<LasFile> const
  lasFileToImport() const { return _lasFileToImport; }

  virtual QVariant
  data(int role, int column) const = 0;

  virtual
  bool
  setData(int role, int column, QVariant value) { return false; }

  virtual QWidget*
  delegateWidget(int column) const;

  virtual void
  setDataFromWidget(QWidget* editor, QModelIndex const& index,
                    QAbstractItemModel* model) {}

  virtual void
  setConnection(std::shared_ptr<IConnection> connection);

  void
  setLasFileToImport(std::shared_ptr<LasFile> lasFileToImport);

protected:

  virtual void
  copyDataToLasToImport() {}

protected:
  TreeEntry* _parent;

  std::shared_ptr<LasFile> _lasFile;

  // contains processed/modified information
  std::shared_ptr<LasFile> _lasFileToImport;

  std::shared_ptr<IConnection> _connection;

  std::vector<std::unique_ptr<TreeEntry>> _entries;
};
}
}
}
