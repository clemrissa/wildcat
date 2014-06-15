#ifndef _GeoImport_ImportTreeModel_hpp_
#define _GeoImport_ImportTreeModel_hpp_

#include <QAbstractItemModel>
#include <QVector>

#include "Las/LasFile.hpp"

namespace Geo {
namespace Import {
namespace TreeWrapper {
class TreeEntry;
class LasFileEntry;
}

class ImportTreeModel: public QAbstractItemModel {
public:
  ImportTreeModel(QVector<TreeWrapper::LasFileEntry*> lasFilesEntries);

  ImportTreeModel(QVector<LasFile::Shared> lasFiles);

  ~ImportTreeModel();

public:
  QVector<TreeWrapper::LasFileEntry*> const
  getLasFileEntries() const;

public:
  virtual
  QVariant
  data(const QModelIndex& index, int role) const override;

  virtual
  QModelIndex
  index(int row, int column, const QModelIndex& parent) const override;

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

private:
  QVector<TreeWrapper::LasFileEntry*> _lasFileEntries;
  QVector<LasFile::Shared>            _lasFiles;

  int
  getEntryPosition(TreeWrapper::TreeEntry* const entry) const;
};
}
}

#endif //  _GeoImport_ImportTreeModel_hpp_
