#include "ImportTreeWrapperWellInformation.hpp"

namespace Geo {
namespace Import {
ImportTreeWrapperWellInformation::
ImportTreeWrapperWellInformation(QSharedPointer<LasFile> lasFile,
                                 ImportTreeWrapperEntry* parent):
  ImportTreeWrapperEntry(lasFile, parent)
{}

QVariant
ImportTreeWrapperWellInformation::
data(int role, int column) {
  if (role != Qt::DisplayRole)
    return QVariant();

  if (column == 0)
    return _lasFile->wellInformation.start;
  else
    return QVariant();
}
}
}
