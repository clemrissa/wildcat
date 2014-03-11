#ifndef Geo_Import_ImportTreeWrapperEntry_hpp
#define Geo_Import_ImportTreeWrapperEntry_hpp

#include <vector>

#include <QSharedPointer>

#include "LasFile.hpp"

namespace Geo {
namespace Import {

/// Composite pattern. Used to represent LAS file strurcture as a tree
class ImportTreeWrapperEntry { 
public:
  ImportTreeWrapperEntry(QSharedPointer<LasFile> lasFile,
                         ImportTreeWrapperEntry* parent = nullptr)
    : _parent(parent),
      _lasFile(lasFile)
  {}


  virtual ~ImportTreeWrapperEntry() {
    for(ImportTreeWrapperEntry* entry: _entries)
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

  QSharedPointer<LasFile> const 
  lasFile() const {
    return _lasFile;
  }

  virtual QVariant
  data(int role, int column) = 0;

private:
  ImportTreeWrapperEntry* _parent;
  QSharedPointer<LasFile> _lasFile);

  std::vector<ImportTreeWrapperEntry*> _entries;

};

}
}
#endif // Geo_Import_ImportTreeWrapperEntry_hpp
