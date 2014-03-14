#ifndef Geo_Import_ImportTreeWrapperEntry_hpp
#define Geo_Import_ImportTreeWrapperEntry_hpp

#include <algorithm>
#include <vector>

#include <QSharedPointer>
#include <QVariant>

#include "LasFile.hpp"

namespace Geo {
namespace Import {
/// Composite pattern. Used to represent LAS file strurcture as a tree
class ImportTreeWrapperEntry: public QObject {
public:
  enum { Name = 0, Description = 1, ImportName = 2, Value = 3, Units = 4, ImportUnits = 5 };

public:
  ImportTreeWrapperEntry(QSharedPointer<LasFile> lasFile,
                         ImportTreeWrapperEntry* parent = nullptr):
    _parent(parent),
    _lasFile(lasFile)
  {}

  virtual
  ~ImportTreeWrapperEntry() {
    for (ImportTreeWrapperEntry* entry : _entries)
      delete entry;
  }

  ImportTreeWrapperEntry*
  parent() {
    return _parent;
  }

  std::vector<ImportTreeWrapperEntry*> const
  entries() const {
    return _entries;
  }

  int
  positionOfChildEntry(ImportTreeWrapperEntry* const childEntry) const {
    auto it = std::find(_entries.begin(), _entries.end(), childEntry);

    return it - _entries.begin();
  }

  QSharedPointer<LasFile> const
  lasFile() const {
    return _lasFile;
  }

  virtual QVariant
  data(int role, int column) = 0;

protected:
  ImportTreeWrapperEntry* _parent;
  QSharedPointer<LasFile> _lasFile;

  std::vector<ImportTreeWrapperEntry*> _entries;
};
}
}
#endif // Geo_Import_ImportTreeWrapperEntry_hpp
