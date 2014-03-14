#ifndef Geo_Import_ImportTreeWrapperLogGroup_hpp
#define Geo_Import_ImportTreeWrapperLogGroup_hpp

#include "ImportTreeWrapperEntry.hpp"

namespace Geo {
namespace Import {
class ImportTreeWrapperLog: public ImportTreeWrapperEntry {
public:
  ImportTreeWrapperLog(QSharedPointer<LasFile> lasFile,
                       ImportTreeWrapperEntry* parent,
                       int                     position):
    ImportTreeWrapperEntry(lasFile, parent),
    _position(position)
  {}

  QVariant
  data(int role, int column) override {
    if (role != Qt::DisplayRole)
      return QVariant();

    QString key = _lasFile->logInformation.keys()[_position];

    switch (column) {
    case ImportTreeWrapperEntry::Name:
      return key + QString(" (%1)").arg(_lasFile->data[key].size());
      break;

    case ImportTreeWrapperEntry::Description:
      return _lasFile->logInformation[key].description;
      break;

    case ImportTreeWrapperEntry::Units:
      return _lasFile->logInformation[key].units;
      break;

    default:
      return QVariant();
      break;
    }
  }

private:
  int _position;
};

class ImportTreeWrapperLogGroup: public ImportTreeWrapperEntry {
public:
  ImportTreeWrapperLogGroup(QSharedPointer<LasFile> lasFile,
                            ImportTreeWrapperEntry* parent):
    ImportTreeWrapperEntry(lasFile, parent) {
    for (int i = 0; i < _lasFile->logInformation.keys().size(); ++i)
      _entries.push_back(new ImportTreeWrapperLog(_lasFile, this, i));
  }

  QVariant
  data(int role, int column) override {
    if (role != Qt::DisplayRole)
      return QVariant();

    switch (column) {
    case 0:
      return tr("Logs (%1)").arg(_lasFile->logInformation.size());
      break;

    default:
      return QVariant();
      break;
    }
  }
};
}
}

#endif // Geo_Import_ImportTreeWrapperLogGroup_hpp
