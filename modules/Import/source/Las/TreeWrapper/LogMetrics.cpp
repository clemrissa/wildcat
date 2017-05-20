#include "LogMetrics.hpp"

using Geo::Import::TreeWrapper::Start;

Start::
Start(std::shared_ptr<LasFile> lasFile,
      TreeEntry*              parent) :
  TreeEntry(lasFile, parent)
{}

QVariant
Start::
data(int role, int column) const
{
  if (role != Qt::DisplayRole)
    return QVariant();

  switch (column)
  {
    case TreeEntry::Name:
      return tr("STRT");
      break;

    case TreeEntry::Description:
      return tr("Start");
      break;

    case TreeEntry::Value:
      return _lasFile->logMetrics.start;
      break;

    case TreeEntry::ImportValue:
      return _lasFileToImport->logMetrics.start;
      break;

    case TreeEntry::Units:
      return _lasFile->logMetrics.units;
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
  _lasFileToImport->logMetrics.start =
    _lasFile->logMetrics.start;
}


// ------------------------------------------------------

using Geo::Import::TreeWrapper::Stop;

Stop::
Stop(std::shared_ptr<LasFile> lasFile,
     TreeEntry*              parent) :
  TreeEntry(lasFile, parent)
{}

QVariant
Stop::
data(int role, int column) const
{
  if (role != Qt::DisplayRole)
    return QVariant();

  switch (column)
  {
    case TreeEntry::Name:
      return tr("STOP");
      break;

    case TreeEntry::Description:
      return tr("Stop");
      break;

    case TreeEntry::Value:
      return _lasFile->logMetrics.stop;
      break;

    case TreeEntry::ImportValue:
      return _lasFileToImport->logMetrics.stop;
      break;

    case TreeEntry::Units:
      return _lasFile->logMetrics.units;
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
  _lasFileToImport->logMetrics.stop =
    _lasFile->logMetrics.stop;
}


// ------------------------------------------------------

using Geo::Import::TreeWrapper::Step;

Step::
Step(std::shared_ptr<LasFile> lasFile,
     TreeEntry*              parent) :
  TreeEntry(lasFile, parent)
{}

QVariant
Step::
data(int role, int column) const
{
  if (role != Qt::DisplayRole)
    return QVariant();

  switch (column)
  {
    case TreeEntry::Name:
      return tr("STEP");
      break;

    case TreeEntry::Description:
      return tr("Step");
      break;

    case TreeEntry::Value:
      return _lasFile->logMetrics.step;
      break;

    case TreeEntry::ImportValue:
      return _lasFileToImport->logMetrics.step;
      break;

    case TreeEntry::Units:
      return _lasFile->logMetrics.units;
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
  _lasFileToImport->logMetrics.step =
    _lasFile->logMetrics.step;
}


// ------------------------------------------------------

using Geo::Import::TreeWrapper::Null;

Null::
Null(std::shared_ptr<LasFile> lasFile,
     TreeEntry*              parent) :
  TreeEntry(lasFile, parent)
{}

QVariant
Null::
data(int role, int column) const
{
  if (role != Qt::DisplayRole)
    return QVariant();

  switch (column)
  {
    case TreeEntry::Name:
      return tr("NULL");
      break;

    case TreeEntry::Description:
      return tr("Null Value");
      break;

    case TreeEntry::Value:
      return _lasFile->logMetrics.nullValue;
      break;

    case TreeEntry::ImportValue:
      return _lasFileToImport->logMetrics.nullValue;
      break;

    case TreeEntry::Units:
      return _lasFile->logMetrics.units;
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
  _lasFileToImport->logMetrics.nullValue =
    _lasFile->logMetrics.nullValue;
}


// ------------------------------------------------------

using Geo::Import::TreeWrapper::LogMetricsGroup;

LogMetricsGroup::
LogMetricsGroup(std::shared_ptr<LasFile> lasFile,
                TreeEntry*              parent) :
  TreeEntry(lasFile, parent)
{
  _entries.push_back(new Start(_lasFile, this));

  _entries.push_back(new Stop(_lasFile, this));

  _entries.push_back(new Step(_lasFile, this));

  _entries.push_back(new Null(_lasFile, this));
}


QVariant
LogMetricsGroup::
data(int role, int column) const
{
  if (role != Qt::DisplayRole)
    return QVariant();

  switch (column)
  {
    case 0:
      return tr("Log Metrics");
      break;

    default:
      return QVariant();
      break;
  }
}
