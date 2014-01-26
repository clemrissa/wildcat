#ifndef Geo_Import_LasFileParser_hpp
#define Geo_Import_LasFileParser_hpp

#include <QtCore/QDateTime>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>

#include "LasFile.hpp"

namespace Geo {
namespace Import {
class LasFileParser {
public:
  LasFile
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

  //  LasFile::WellInformation wellInformation;

  LasFile lasFile;
};
}
}

#endif
