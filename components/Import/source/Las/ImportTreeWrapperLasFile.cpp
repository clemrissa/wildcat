#include "ImportTreeWrapperLasFile.hpp"

#include "ImportTreeWrapperWellInformation.hpp"
#include "ImportTreeWrapperLogGroup.hpp"
#include "ImportTreeWrapperParameters.hpp"

namespace Geo {
namespace Import {
/// Composite pattern. Used to represent LAS file strurcture as a tree

ImportTreeWrapperLasFile::
ImportTreeWrapperLasFile(QSharedPointer<LasFile> lasFile):
  ImportTreeWrapperEntry(lasFile) {
  _entries.push_back(new ImportTreeWrapperWellName(_lasFile,
                                                   this));

  _entries.push_back(new ImportTreeWrapperWellStart(_lasFile,
                                                    this));

  _entries.push_back(new ImportTreeWrapperWellStop(_lasFile,
                                                   this));

  _entries.push_back(new ImportTreeWrapperWellStep(_lasFile,
                                                   this));

  _entries.push_back(new ImportTreeWrapperWellNull(_lasFile,
                                                   this));

  for (int i = 0; i < _lasFile->wellInformation.entries.keys().size(); ++i)
    _entries.push_back(new ImportTreeWrapperWellInfo(_lasFile, this, i));

  _entries.push_back(new ImportTreeWrapperLogGroup(_lasFile,
                                                   this));

  _entries.push_back(new ImportTreeWrapperParameterGroup(_lasFile,
                                                         this));
}

QVariant
ImportTreeWrapperLasFile::
data(int role, int column) {
  if (role != Qt::DisplayRole)
    return QVariant();

  switch (column) {
  case ImportTreeWrapperEntry::Name:
    return tr("File");
    break;

  case ImportTreeWrapperEntry::Description:
    return _lasFile->fileName;
    break;

  default:
    return QVariant();
    break;
  }
}
}
}
