#ifndef Geo_Import_LasFileParser_hpp
#define Geo_Import_LasFileParser_hpp

#include <QtCore/QDateTime>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>

#include <QSharedPointer>

#include "LasFile.hpp"

namespace Geo {
namespace Import {
class LasFileParser: public QObject
{
  Q_OBJECT

public:
  QSharedPointer<LasFile>
  parse(const QString fileName);

private:
  bool
  parseVersionSection(QSharedPointer<LasFile>& lasFile, int& lineNumber);

  void
  parseWellInformationSection(QSharedPointer<LasFile>& lasFile,
                              int&                     lineNumber);

  void
  parseLogInformationSection(QSharedPointer<LasFile>& lasFile,
                             int&                     lineNumber);

  void
  parseParameterInformationSection(QSharedPointer<LasFile>& lasFile,
                                   int&                     lineNumber);

  void
  parseOtherInformationSection(QSharedPointer<LasFile>& lasFile,
                               int&                     lineNumber);

  void
  parseAsciiLogDataSection(QSharedPointer<LasFile>& lasFile, int& lineNumber);

  void
  parseLines(QSharedPointer<LasFile>& lasFile);

private:
  QStringList _lines;

  int _version;
  bool    _wrap;
};
}
}

#endif
