#ifndef Geo_Import_ImportTreeWrapperParameters_hpp
#define Geo_Import_ImportTreeWrapperParameters_hpp

#include "ImportTreeWrapperEntry.hpp"


namespace Geo {
namespace Import {
class ImportTreeWrapperParameter: public ImportTreeWrapperEntry {
public:
  ImportTreeWrapperParameter(QSharedPointer<LasFile> lasFile,
                             ImportTreeWrapperEntry* parent,
                             int                     position):
    ImportTreeWrapperEntry(lasFile, parent),
    _position(position)
  {}

  QVariant
  data(int role, int column) override {
    if (role != Qt::DisplayRole)
      return QVariant();

    QString key = _lasFile->parameterInformation.keys()[_position];

    switch (column) {
    case ImportTreeWrapperEntry::Name:
      return _lasFile->parameterInformation[key].name;
      break;

    case ImportTreeWrapperEntry::Units:
      return _lasFile->parameterInformation[key].units;
      break;

    case ImportTreeWrapperEntry::Value:
      return _lasFile->parameterInformation[key].value;
      break;

    case ImportTreeWrapperEntry::Description:
      return _lasFile->parameterInformation[key].description;
      break;

    default:
      return QVariant();
      break;
    }
  }

private:
  int _position;
};


class ImportTreeWrapperParameterGroup: public ImportTreeWrapperEntry {
public:
  ImportTreeWrapperParameterGroup(QSharedPointer<LasFile> lasFile,
                                  ImportTreeWrapperEntry* parent):
    ImportTreeWrapperEntry(lasFile, parent) {
    for (int i = 0; i < _lasFile->parameterInformation.keys().size(); ++i)
      _entries.push_back(new ImportTreeWrapperParameter(_lasFile, this, i));
  }

  QVariant
  data(int role, int column) override {
    if (role != Qt::DisplayRole)
      return QVariant();

    switch (column) {
    case 0:
      return tr("Parameters (%1)").arg(_lasFile->parameterInformation.size());
      break;

    default:
      return QVariant();
      break;
    }
  }
};
}
}

#endif // Geo_Import_ImportTreeWrapperParameters_hpp
