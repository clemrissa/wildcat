#include "LasFile.hpp"

#include <QtCore/QStringList>

namespace Geo
{
namespace Import
{
//

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

//
}
}
