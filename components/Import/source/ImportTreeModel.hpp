#ifndef _GeoImport_ImportTreeModel_hpp_
#define _GeoImport_ImportTreeModel_hpp_

#include <QAbstractItemModel>
#include <QVector>

namespace Geo {
namespace Import {
class ImportTreeWrapperLasFile;
class ImportTreeWrapperEntry;

class ImportTreeModel: public QAbstractItemModel {
public:
  ImportTreeModel(QVector<ImportTreeWrapperLasFile*> importTreeWrapperLasFiles);

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
  QVector<ImportTreeWrapperLasFile*> _importTreeWrapperLasFiles;

  int
  getEntryPosition(ImportTreeWrapperEntry* const entry) const;
};
}
}

#endif //  _GeoImport_ImportTreeModel_hpp_
