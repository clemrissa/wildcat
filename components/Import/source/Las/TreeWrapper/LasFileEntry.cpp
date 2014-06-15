#include "LasFileEntry.hpp"

#include "LogGroup.hpp"
#include "Parameters.hpp"
#include "WellInformation.hpp"

#include <QColor>

using Geo::Import::TreeWrapper::LasFileEntry;

/// Composite pattern. Used to represent LAS file strurcture as a tree

LasFileEntry::
LasFileEntry(QSharedPointer<LasFile> lasFile):
  TreeEntry(lasFile)
{
  _entries.push_back(new WellName(_lasFile,
                                  this));

  _entries.push_back(new WellStart(_lasFile,
                                   this));

  _entries.push_back(new WellStop(_lasFile,
                                  this));

  _entries.push_back(new WellStep(_lasFile,
                                  this));

  _entries.push_back(new WellNull(_lasFile,
                                  this));

  for (int i = 0; i < _lasFile->wellInformation.entries.keys().size(); ++i)
    _entries.push_back(new WellInfo(_lasFile, this, i));

  _entries.push_back(new LogGroup(_lasFile,
                                  this));

  _entries.push_back(new ParameterGroup(_lasFile,
                                        this));
}


QVariant
LasFileEntry::
data(int role, int column)
{
  switch (role) {
  case Qt::DisplayRole: {
    switch (column) {
    case TreeEntry::Name:
      return tr("File");
      break;

    case TreeEntry::Description:
      return _lasFile->fileName;
      break;

    default:
      return QVariant();
      break;
    }

    break;
  }

  case Qt::BackgroundRole:
    return QVariant(QColor(0xCC, 0xDD, 0xEE));
    break;
  }

  return QVariant();
}
