#ifndef Geo_Import_LogGroup_hpp
#define Geo_Import_LogGroup_hpp

#include "TreeEntry.hpp"

namespace Geo {
namespace Import {
namespace TreeWrapper {
class ImportTreeWrapperLog: public TreeEntry {
public:
  ImportTreeWrapperLog(QSharedPointer<LasFile> lasFile,
                       TreeEntry*              parent,
                       int                     position):
    TreeEntry(lasFile, parent),
    _position(position)
  {}

  QVariant
  data(int role, int column) override
  {
    if (role != Qt::DisplayRole)
      return QVariant();

    QString key = _lasFile->logInformation.keys()[_position];

    switch (column) {
    case TreeEntry::Name:
      return key + QString(" (%1)").arg(_lasFile->data[key].size());
      break;

    case TreeEntry::Description:
      return _lasFile->logInformation[key].description;
      break;

    case TreeEntry::Units:
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

class LogGroup: public TreeEntry {
public:
  LogGroup(QSharedPointer<LasFile> lasFile,
           TreeEntry*              parent):
    TreeEntry(lasFile, parent)
  {
    for (int i = 0; i < _lasFile->logInformation.keys().size(); ++i)
      _entries.push_back(new ImportTreeWrapperLog(_lasFile, this, i));
  }


  QVariant
  data(int role, int column) override
  {
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
}

#endif // Geo_Import_LogGroup_hpp
