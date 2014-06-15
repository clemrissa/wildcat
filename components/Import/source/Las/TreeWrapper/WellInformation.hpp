#ifndef Geo_Import_WellInformation_hpp
#define Geo_Import_WellInformation_hpp

#include "TreeEntry.hpp"

namespace Geo {
namespace Import {
namespace TreeWrapper {
//
class WellName: public TreeEntry {
public:
  WellName(QSharedPointer<LasFile> lasFile,
           TreeEntry*              parent):
    TreeEntry(lasFile, parent)
  {}

  QVariant
  data(int role, int column) override
  {
    if (role != Qt::DisplayRole)
      return QVariant();

    switch (column) {
    case TreeEntry::Name:
      return tr("Well");
      break;

    case TreeEntry::Value:
      return _lasFile->wellInformation.wellName;
      break;

    default:
      return QVariant();
      break;
    }
  }
};

class WellStart: public TreeEntry {
public:
  WellStart(QSharedPointer<LasFile> lasFile,
            TreeEntry*              parent):
    TreeEntry(lasFile, parent)
  {}

  QVariant
  data(int role, int column) override
  {
    if (role != Qt::DisplayRole)
      return QVariant();

    switch (column) {
    case TreeEntry::Name:
      return tr("Start");
      break;

    case TreeEntry::Value:
      return _lasFile->wellInformation.start;
      break;

    case TreeEntry::Units:
      return _lasFile->wellInformation.units;
      break;

    default:
      return QVariant();
      break;
    }
  }
};

class WellStop: public TreeEntry {
public:
  WellStop(QSharedPointer<LasFile> lasFile,
           TreeEntry*              parent):
    TreeEntry(lasFile, parent)
  {}

  QVariant
  data(int role, int column) override
  {
    if (role != Qt::DisplayRole)
      return QVariant();

    switch (column) {
    case TreeEntry::Name:
      return tr("Stop");
      break;

    case TreeEntry::Value:
      return _lasFile->wellInformation.stop;
      break;

    case TreeEntry::Units:
      return _lasFile->wellInformation.units;
      break;

    default:
      return QVariant();
      break;
    }
  }
};

class WellStep: public TreeEntry {
public:
  WellStep(QSharedPointer<LasFile> lasFile,
           TreeEntry*              parent):
    TreeEntry(lasFile, parent)
  {}

  QVariant
  data(int role, int column) override
  {
    if (role != Qt::DisplayRole)
      return QVariant();

    switch (column) {
    case TreeEntry::Name:
      return tr("Step");
      break;

    case TreeEntry::Value:
      return _lasFile->wellInformation.step;
      break;

    case TreeEntry::Units:
      return _lasFile->wellInformation.units;
      break;

    default:
      return QVariant();
      break;
    }
  }
};

class WellNull: public TreeEntry {
public:
  WellNull(QSharedPointer<LasFile> lasFile,
           TreeEntry*              parent):
    TreeEntry(lasFile, parent)
  {}

  QVariant
  data(int role, int column) override
  {
    if (role != Qt::DisplayRole)
      return QVariant();

    switch (column) {
    case TreeEntry::Name:
      return tr("Null");
      break;

    case TreeEntry::Value:
      return _lasFile->wellInformation.nullValue;
      break;

    case TreeEntry::Units:
      return _lasFile->wellInformation.units;
      break;

    default:
      return QVariant();
      break;
    }
  }
};

class WellInfo: public TreeEntry {
public:
  WellInfo(QSharedPointer<LasFile> lasFile,
           TreeEntry*              parent,
           int                     position):
    TreeEntry(lasFile, parent), _position(position)
  {}

  QVariant
  data(int role, int column) override
  {
    if (role != Qt::DisplayRole)
      return QVariant();

    QString key = _lasFile->wellInformation.entries.keys()[_position];

    switch (column) {
    case TreeEntry::Name:
      return _lasFile->wellInformation.entries[key].name;
      break;

    case TreeEntry::Description:
      return _lasFile->wellInformation.entries[key].description;
      break;

    case TreeEntry::Value:
      return _lasFile->wellInformation.entries[key].value;
      break;

    case TreeEntry::Units:
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
}

#endif // Geo_Import_WellInformation_hpp
