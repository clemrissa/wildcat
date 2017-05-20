#pragma once

#include <QtCore/QStringList>
#include <QtCore/QString>

#include "LasFile.hpp"

namespace Geo {
namespace Import {

class LasFileParser : public QObject
{
  Q_OBJECT

public:
  std::shared_ptr<LasFile>
  parse(const QString fileName);

private:
  bool
  parseVersionSection(std::shared_ptr<LasFile>& lasFile, int& lineNumber);

  void
  parseWellInformationSection(std::shared_ptr<LasFile>& lasFile,
                              int&                     lineNumber);

  void
  parseLogInformationSection(std::shared_ptr<LasFile>& lasFile,
                             int&                     lineNumber);

  void
  parseParameterInformationSection(std::shared_ptr<LasFile>& lasFile,
                                   int&                     lineNumber);

  void
  parseOtherInformationSection(std::shared_ptr<LasFile>& lasFile,
                               int&                     lineNumber);

  void
  parseAsciiLogDataSection(std::shared_ptr<LasFile>& lasFile, int& lineNumber);

  void
  parseLines(std::shared_ptr<LasFile>& lasFile);

private:
  QStringList _lines;

  int _version;
  bool _wrap;
};
}
}
