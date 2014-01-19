#include "LasFile.hpp"

#include <QtCore/QStringList>

namespace Geo {
namespace Import {
//

QString
LASFile::
getText() const {
  //
  QStringList list;

  list << "------";
  list << "well information";

  list << "well:   " + wellInformation.wellName;
  list << "start:  " + QString::number(wellInformation.start);
  list << "stop:   " + QString::number(wellInformation.stop);

  for (auto entry : wellInformation.entries)
    list << entry.name + "   " + entry.value;

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
