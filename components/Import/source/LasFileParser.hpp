#ifndef Geo_Import_LASFileParser_hpp
#define Geo_Import_LASFileParser_hpp

#include <QtCore/QDateTime>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>

#include "LasFile.hpp"

namespace Geo {
namespace Import {
class LASFileParser {
public:
  LASFile
  parse(const QString fileName);

private:
  bool
  parseVersionSection(int& lineNumber);

  void
  parseWellInformationSection(int& lineNumber);

  void
  parseCurveInformationSection(int& lineNumber);

  void
  parseParameterInformationSection(int& lineNumber);

  void
  parseOtherInformationSection(int& lineNumber);

  void
  parseAsciiLogDataSection(int& lineNumber);

  void
  parseLines();

private:
  QStringList _lines;

  QString _version;
  bool    _wrap;

  //  LASFile::WellInformation wellInformation;

  LASFile lasFile;
};
}
}

#endif
