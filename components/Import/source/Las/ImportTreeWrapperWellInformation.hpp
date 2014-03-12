#ifndef Geo_Import_ImportTreeWrapperWellInformation_hpp
#define Geo_Import_ImportTreeWrapperWellInformation_hpp

#include "ImportTreeWrapperEntry.hpp"

namespace Geo {
namespace Import {
class ImportTreeWrapperWellInformation: public ImportTreeWrapperEntry {
public:
  ImportTreeWrapperWellInformation(QSharedPointer<LasFile> lasFile,
                                   ImportTreeWrapperEntry* parent);

  QVariant
  data(int role, int column) override;
};
}
}

#endif // Geo_Import_ImportTreeWrapperWellInformation_hpp
