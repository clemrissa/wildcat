#include "LasFile.hpp"

#include <QtCore/QStringList>

namespace Geo {
namespace Import {
//

LasFile::
LasFile(LasFile const &lasFile) {
  wellInformation.start = lasFile.wellInformation.start;
  wellInformation.stop  = lasFile.wellInformation.stop;
  wellInformation.step  = lasFile.wellInformation.step;
  wellInformation.nullValue = lasFile.wellInformation.nullValue;
  wellInformation.units = lasFile.wellInformation.units;

  for(auto key : lasFile.wellInformation.entries.keys())
  {
    wellInformation.entries[key] = lasFile.wellInformation.entries[key];
  }

  for(auto key : lasFile.parameterInformation.keys())
  {
    parameterInformation[key] = lasFile.parameterInformation[key];
  }

  for(auto key : lasFile.logInformation.keys())
  {
    logInformation[key] = lasFile.logInformation[key];
  }

  for(auto key : lasFile.data.keys())
  {
    data[key] = lasFile.data[key];
  }
}

QString
LasFile::
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
