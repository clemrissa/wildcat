#include "LasFileEntry.hpp"

#include <QtGui/QColor>

#include "LasRequired.hpp"
#include "LogGroup.hpp"
#include "LogMetrics.hpp"
#include "Parameters.hpp"
#include "WellInformation.hpp"

using Geo::Import::TreeWrapper::LasFileEntry;

/// Composite pattern. Used to represent LAS file strurcture as a tree

LasFileEntry::
LasFileEntry(LasFile::Shared lasFile) :
  TreeEntry(lasFile)
{
  createEntries(lasFile);

  setLasFileToImport(LasFile::Shared(new LasFile()));
}


void
LasFileEntry::
createEntries(LasFile::Shared lasFile)
{
  _entries.push_back(new LasRequiredGroup(lasFile, this));

  _entries.push_back(new WellInformationGroup(lasFile,  this));

  _entries.push_back(new LogMetricsGroup(lasFile, this));

  _entries.push_back(new LogGroup(_lasFile, this));

  _entries.push_back(new ParameterGroup(_lasFile, this));
}


QVariant
LasFileEntry::
data(int role, int column) const
{
  switch (role)
  {
    case Qt::DisplayRole:
    {
      switch (column)
      {
        case TreeEntry::Name:
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
