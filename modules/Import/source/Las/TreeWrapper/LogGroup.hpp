#pragma once

#include "TreeEntry.hpp"

namespace Geo {
namespace Import {
namespace TreeWrapper {
//

class LogWrapper : public TreeEntry
{
public:
  LogWrapper(std::shared_ptr<LasFile> lasFile,
             TreeEntry*              parent,
             int position) :
    TreeEntry(lasFile, parent),
    _position(position)
  {}

  QVariant
  data(int role, int column) const override
  {
    if (role != Qt::DisplayRole)
      return QVariant();

    QString key = _lasFile->logInformation.keys()[_position];

    switch (column)
    {
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

class LogGroup : public TreeEntry
{
public:
  LogGroup(std::shared_ptr<LasFile> lasFile,
           TreeEntry*              parent) 
    : TreeEntry(lasFile, parent)
  {
    for (int i = 0; i < _lasFile->logInformation.keys().size(); ++i)
      _entries.push_back(new LogWrapper(_lasFile, this, i));
  }

  QVariant
  data(int role, int column) const override
  {
    if (role != Qt::DisplayRole)
      return QVariant();

    switch (column)
    {
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
