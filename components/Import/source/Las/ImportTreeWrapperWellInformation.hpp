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

    switch (column) {
    case ImportTreeWrapperEntry::Name:
      return tr("Well");
      break;

    case ImportTreeWrapperEntry::Value:
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

    switch (column) {
    case ImportTreeWrapperEntry::Name:
      return tr("Start");
      break;

    case ImportTreeWrapperEntry::Value:
      return _lasFile->wellInformation.start;
      break;

    case ImportTreeWrapperEntry::Units:
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

    switch (column) {
    case ImportTreeWrapperEntry::Name:
      return tr("Stop");
      break;

    case ImportTreeWrapperEntry::Value:
      return _lasFile->wellInformation.stop;
      break;

    case ImportTreeWrapperEntry::Units:
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

    switch (column) {
    case ImportTreeWrapperEntry::Name:
      return tr("Step");
      break;

    case ImportTreeWrapperEntry::Value:
      return _lasFile->wellInformation.step;
      break;

    case ImportTreeWrapperEntry::Units:
      return _lasFile->wellInformation.units;
      break;

    default:
      return QVariant();
      break;
    }
  }
};

class ImportTreeWrapperWellNull: public ImportTreeWrapperEntry {
public:
  ImportTreeWrapperWellNull(QSharedPointer<LasFile> lasFile,
                            ImportTreeWrapperEntry* parent):
    ImportTreeWrapperEntry(lasFile, parent)
  {}

  QVariant
  data(int role, int column) override {
    if (role != Qt::DisplayRole)
      return QVariant();

    switch (column) {
    case ImportTreeWrapperEntry::Name:
      return tr("Null");
      break;

    case ImportTreeWrapperEntry::Value:
      return _lasFile->wellInformation.nullValue;
      break;

    case ImportTreeWrapperEntry::Units:
      return _lasFile->wellInformation.units;
      break;

    default:
      return QVariant();
      break;
    }
  }
};

class ImportTreeWrapperWellInfo: public ImportTreeWrapperEntry {
public:
  ImportTreeWrapperWellInfo(QSharedPointer<LasFile> lasFile,
                            ImportTreeWrapperEntry* parent,
                            int                     position):
    ImportTreeWrapperEntry(lasFile, parent),
    _position(position)
  {}

  QVariant
  data(int role, int column) override {
    if (role != Qt::DisplayRole)
      return QVariant();

    QString key = _lasFile->wellInformation.entries.keys()[_position];

    switch (column) {
    case ImportTreeWrapperEntry::Name:
      return _lasFile->wellInformation.entries[key].name;
      break;

    case ImportTreeWrapperEntry::Description:
      return _lasFile->wellInformation.entries[key].description;
      break;

    case ImportTreeWrapperEntry::Value:
      return _lasFile->wellInformation.entries[key].value;
      break;

    case ImportTreeWrapperEntry::Units:
      return _lasFile->wellInformation.entries[key].units;
      break;

    default:
      return QVariant();
      break;
    }
  }

private:
  int _position;
};
}
}

#endif // Geo_Import_ImportTreeWrapperWellInformation_hpp
