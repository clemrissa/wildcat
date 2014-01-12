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
    list << entry.mnem + "   " + entry.value;

  list << "";
  list << "------";
  list << "curves";

  for (auto entry : data)
    list << entry.first + "   " + QString::number(entry.second.size());

  return list.join("\n");
}
}
}
