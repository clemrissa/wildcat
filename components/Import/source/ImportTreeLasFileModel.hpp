#ifndef _GeoImport_ImportTreeLasFileModel_h_
#define _GeoImport_ImportTreeLasFileModel_h_

#include <QAbstractItemModel>
#include <QSharedPointer>

#include "LasFile.hpp"

namespace Geo {
namespace Import {
class ImportTreeLasFileModel: public QAbstractItemModel {
public:
  ImportTreeLasFileModel(QSharedPointer<LasFile> lasFile);

  QVariant
  data(const QModelIndex& index, int role) const override;

  QModelIndex
  index(int row, int column, const QModelIndex& parent) const override;

  QModelIndex
  parent(const QModelIndex& index) const override;

  int
  columnCount(const QModelIndex& parent) const override;

  int
  rowCount(const QModelIndex& parent) const override;

public:
  QSharedPointer<LasFile>
  getLasFile() const;

private:
  QSharedPointer<LasFile> _lasFile;

  //
};
}
}

#endif //  _GeoImport_ImportTreeLasFileModel_h_
