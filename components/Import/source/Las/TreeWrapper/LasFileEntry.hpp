#ifndef Geo_Import_LasFileEntry_hpp
#define Geo_Import_LasFileEntry_hpp

#include "TreeEntry.hpp"

namespace Geo {
namespace Import {
namespace TreeWrapper {
/// Composite pattern. Used to represent LAS file strurcture as a tree
class LasFileEntry: public TreeEntry {
public:
  LasFileEntry(QSharedPointer<LasFile> lasFile);

  virtual QVariant
  data(int role, int column) override;
};
}
}
}
#endif // Geo_Import_LasFileEntry_hpp
