#ifndef Geo_Import_Parameters_hpp
#define Geo_Import_Parameters_hpp

#include "TreeEntry.hpp"

namespace Geo {
namespace Import {
namespace TreeWrapper {
//

class Parameter:
  public TreeEntry
{
public:
  Parameter(QSharedPointer<LasFile> lasFile,
            TreeEntry*              parent,
            int                     position):
    TreeEntry(lasFile, parent),
    _position(position)
  {
  }

  QVariant
  data(int role, int column) override
  {
    if (role != Qt::DisplayRole)
      return QVariant();

    QString key = _lasFile->parameterInformation.keys()[_position];

    switch (column) {
    case TreeEntry::Name:
      return _lasFile->parameterInformation[key].name;
      break;

    case TreeEntry::Units:
      return _lasFile->parameterInformation[key].units;
      break;

    case TreeEntry::Value:
      return _lasFile->parameterInformation[key].value;
      break;

    case TreeEntry::Description:
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

class ParameterGroup: public TreeEntry
{
public:
  ParameterGroup(QSharedPointer<LasFile> lasFile,
                 TreeEntry*              parent):
    TreeEntry(lasFile, parent)
  {
    for (int i = 0; i < _lasFile->parameterInformation.keys().size(); ++i)
      _entries.push_back(new Parameter(_lasFile, this, i));
  }

  QVariant
  data(int role, int column) override
  {
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
}

#endif // Geo_Import_Parameters_hpp
