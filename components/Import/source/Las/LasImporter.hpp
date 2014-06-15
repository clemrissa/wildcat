#ifndef Geo_Import_Importer_hpp
#define Geo_Import_Importer_hpp

#include <QVector>

#include "Las/LasFile.hpp"

namespace Geo {
namespace Import {
// TODO add namespace Las

class LasImporter {
  //

public:
  LasImporter(int databaseIndex);

public:
  void
  import(QVector<LasFile::Shared> lasFiles);

private:
  int _databaseIndex;
};
}
}
#endif //  Geo_Import_Importer_hpp
