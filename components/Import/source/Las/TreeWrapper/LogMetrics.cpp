#include "LogMetrics.hpp"

using Geo::Import::TreeWrapper::Start;

Start::
Start(QSharedPointer<LasFile> lasFile,
          TreeEntry*              parent):
  TreeEntry(lasFile, parent)
{
}


QVariant
Start::
data(int role, int column)
{
  if (role != Qt::DisplayRole)
    return QVariant();

  switch (column) {
  case TreeEntry::Name:
    return tr("STRT");
    break;

  case TreeEntry::Description:
    return tr("Start");
    break;

  case TreeEntry::Value:
    return _lasFile->lasRequired.start;
    break;

  case TreeEntry::ImportValue:
    return _lasFileToImport->lasRequired.start;
    break;

  case TreeEntry::Units:
    return _lasFile->lasRequired.units;
    break;

  default:
    return QVariant();
    break;
  }
}


void
Start::
copyDataToLasToImport()
{
  _lasFileToImport->lasRequired.start =
    _lasFile->lasRequired.start;
}


//------------------------------------------------------

using Geo::Import::TreeWrapper::Stop;


Stop::
Stop(QSharedPointer<LasFile> lasFile,
         TreeEntry*              parent):
  TreeEntry(lasFile, parent)
{
}


QVariant
Stop::
data(int role, int column)
{
  if (role != Qt::DisplayRole)
    return QVariant();

  switch (column) {
  case TreeEntry::Name:
    return tr("STOP");
    break;

  case TreeEntry::Description:
    return tr("Stop");
    break;

  case TreeEntry::Value:
    return _lasFile->lasRequired.stop;
    break;

  case TreeEntry::ImportValue:
    return _lasFileToImport->lasRequired.stop;
    break;

  case TreeEntry::Units:
    return _lasFile->lasRequired.units;
    break;

  default:
    return QVariant();
    break;
  }
}


void
Stop::
copyDataToLasToImport()
{
  _lasFileToImport->lasRequired.stop =
    _lasFile->lasRequired.stop;
}



//------------------------------------------------------

using Geo::Import::TreeWrapper::Step;


Step::
Step(QSharedPointer<LasFile> lasFile,
         TreeEntry*              parent):
  TreeEntry(lasFile, parent)
{
}


QVariant
Step::
data(int role, int column)
{
  if (role != Qt::DisplayRole)
    return QVariant();

  switch (column) {
  case TreeEntry::Name:
    return tr("STEP");
    break;

  case TreeEntry::Description:
    return tr("Step");
    break;

  case TreeEntry::Value:
    return _lasFile->lasRequired.step;
    break;

  case TreeEntry::ImportValue:
    return _lasFileToImport->lasRequired.step;
    break;

  case TreeEntry::Units:
    return _lasFile->lasRequired.units;
    break;

  default:
    return QVariant();
    break;
  }
}

void
Step::
copyDataToLasToImport()
{
  _lasFileToImport->lasRequired.step =
    _lasFile->lasRequired.step;
}


//------------------------------------------------------


using Geo::Import::TreeWrapper::Null;

Null::
Null(QSharedPointer<LasFile> lasFile,
         TreeEntry*              parent):
  TreeEntry(lasFile, parent)
{
}

QVariant
Null::
data(int role, int column)
{
  if (role != Qt::DisplayRole)
    return QVariant();

  switch (column) {
  case TreeEntry::Name:
    return tr("NULL");
    break;

  case TreeEntry::Description:
    return tr("Null Value");
    break;

  case TreeEntry::Value:
    return _lasFile->lasRequired.nullValue;
    break;

  case TreeEntry::ImportValue:
    return _lasFileToImport->lasRequired.nullValue;
    break;

  case TreeEntry::Units:
    return _lasFile->lasRequired.units;
    break;

  default:
    return QVariant();
    break;
  }
}


void
Null::
copyDataToLasToImport()
{
  _lasFileToImport->lasRequired.nullValue =
    _lasFile->lasRequired.nullValue;
}



//------------------------------------------------------


using Geo::Import::TreeWrapper::LogMetricsGroup;


LogMetricsGroup::
LogMetricsGroup(QSharedPointer<LasFile> lasFile,
                TreeEntry*              parent):
  TreeEntry(lasFile, parent)
{
  _entries.push_back(new Start(_lasFile, this));

  _entries.push_back(new Stop(_lasFile, this));

  _entries.push_back(new Step(_lasFile, this));

  _entries.push_back(new Null(_lasFile, this));
}


QVariant
LogMetricsGroup::
data(int role, int column)
{
  if (role != Qt::DisplayRole)
    return QVariant();

  switch (column) {
  case 0:
    return tr("Log Metrics");
    break;

  default:
    return QVariant();
    break;
  }
}
