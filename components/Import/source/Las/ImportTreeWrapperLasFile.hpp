#ifndef Geo_Import_ImportTreeWrapperLasFile_hpp
#define Geo_Import_ImportTreeWrapperLasFile_hpp

#include "ImportTreeWrapperEntry.hpp"

namespace Geo {
namespace Import {

/// Composite pattern. Used to represent LAS file strurcture as a tree
class ImportTreeWrapperLasFile : public ImportTreeWrapperEntry
public:
  ImportTreeWrapperLasFile(QSharedPointer<LasFile> lasFile);

  virtual QVariant
  data(int role, int column) override;
};

}
}
#endif // Geo_Import_ImportTreeWrapperLasFile_hpp

