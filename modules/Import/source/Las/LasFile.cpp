#include "LasFile.hpp"

#include <QtCore/QStringList>

namespace Geo {
namespace Import {
//

LasFile::
LasFile(LasFile const& lasFile)
{
  logMetrics.start     = lasFile.logMetrics.start;
  logMetrics.stop      = lasFile.logMetrics.stop;
  logMetrics.step      = lasFile.logMetrics.step;
  logMetrics.nullValue = lasFile.logMetrics.nullValue;
  logMetrics.units     = lasFile.logMetrics.units;

  for (auto key : lasFile.wellInformation.keys())
    wellInformation[key] = lasFile.wellInformation[key];

  for (auto key : lasFile.parameterInformation.keys())
    parameterInformation[key] = lasFile.parameterInformation[key];

  for (auto key : lasFile.logInformation.keys())
    logInformation[key] = lasFile.logInformation[key];

  for (auto key : lasFile.data.keys())
    data[key] = lasFile.data[key];
}


QString
LasFile::
getText() const
{
  //
  QStringList list;

  list << "------";
  list << "well information";

  list << "well:   " + lasRequired.wellName;
  list << "start:  " + QString::number(logMetrics.start);
  list << "stop:   " + QString::number(logMetrics.stop);

  for (auto key : wellInformation.keys())
    list << key + "   " + wellInformation[key].value;

  list << "";
  list << "------";
  list << "curves";

  for (auto entryKey : data.keys())
    list << entryKey
      + " has "
      + QString::number(data[entryKey].size())
      + " numbers.";

  return list.join("\n");
}
}
}
