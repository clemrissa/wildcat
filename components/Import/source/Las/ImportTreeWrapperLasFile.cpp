#include "ImportTreeWrapperLasFile.hpp"

#include "ImportTreeWrapperWellInformation.hpp"

namespace Geo {
namespace Import {
/// Composite pattern. Used to represent LAS file strurcture as a tree

ImportTreeWrapperLasFile::
ImportTreeWrapperLasFile(QSharedPointer<LasFile> lasFile):
  ImportTreeWrapperEntry(lasFile) {
  _entries.push_back(new ImportTreeWrapperWellInformation(_lasFile,
                                                          this));
}

QVariant
ImportTreeWrapperLasFile::
data(int role, int column) {
  if (role != Qt::DisplayRole)
    return QVariant();

  if (column == 0)
    return _lasFile->wellInformation.wellName;
  else
    return QVariant();
}
}
}
