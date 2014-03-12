#ifndef Geo_Import_ImportTreeWrapperWellInformation_hpp
#define Geo_Import_ImportTreeWrapperWellInformation_hpp

#include "ImportTreeWrapperEntry.hpp"

namespace Geo {
namespace Import {
class ImportTreeWrapperWellName: public ImportTreeWrapperEntry {
public:
  ImportTreeWrapperWellName(QSharedPointer<LasFile> lasFile,
                            ImportTreeWrapperEntry* parent):
  ImportTreeWrapperEntry(lasFile, parent)
{}

  QVariant
  data(int role, int column) override {
    if (role != Qt::DisplayRole)
      return QVariant();

    switch(column){
      case 0:
        return tr("Well");
        break;
      case 1:
        return _lasFile->wellInformation.wellName;
        break;
      default:
        return QVariant();
        break;
    }
  }
};


class ImportTreeWrapperWellStart: public ImportTreeWrapperEntry {
public:
  ImportTreeWrapperWellStart(QSharedPointer<LasFile> lasFile,
                            ImportTreeWrapperEntry* parent):
  ImportTreeWrapperEntry(lasFile, parent)
  {}

  QVariant
  data(int role, int column) override {
    if (role != Qt::DisplayRole)
      return QVariant();

    switch(column){
      case 0:
        return tr("Start");
        break;
      case 1:
        return _lasFile->wellInformation.start;
        break;

      case 3:
        return _lasFile->wellInformation.units;
        break;

      default:
        return QVariant();
        break;
    }
  }
};

class ImportTreeWrapperWellStop: public ImportTreeWrapperEntry {
public:
  ImportTreeWrapperWellStop(QSharedPointer<LasFile> lasFile,
                            ImportTreeWrapperEntry* parent):
  ImportTreeWrapperEntry(lasFile, parent)
  {}

  QVariant
  data(int role, int column) override {
    if (role != Qt::DisplayRole)
      return QVariant();

    switch(column){
      case 0:
        return tr("Stop");
        break;
      case 1:
        return _lasFile->wellInformation.stop;
        break;

      case 3:
        return _lasFile->wellInformation.units;
        break;

      default:
        return QVariant();
        break;
    }
  }
};

class ImportTreeWrapperWellStep: public ImportTreeWrapperEntry {
public:
  ImportTreeWrapperWellStep(QSharedPointer<LasFile> lasFile,
                            ImportTreeWrapperEntry* parent):
  ImportTreeWrapperEntry(lasFile, parent)
  {}

  QVariant
  data(int role, int column) override {
    if (role != Qt::DisplayRole)
      return QVariant();

    switch(column){
      case 0:
        return tr("Step");
        break;
      case 1:
        return _lasFile->wellInformation.step;
        break;

      case 3:
        return _lasFile->wellInformation.units;
        break;

      default:
        return QVariant();
        break;
    }
  }
};
}
}

#endif // Geo_Import_ImportTreeWrapperWellInformation_hpp
