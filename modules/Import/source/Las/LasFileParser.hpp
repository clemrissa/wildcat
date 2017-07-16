#pragma once

#include <vector>

#include <QtCore/QString>

#include "LasFile.hpp"

namespace Geo
{
namespace Import
{

class LasFileParser : public QObject
{
  Q_OBJECT

public:
  std::shared_ptr<LasFile>
  parse(QString const & fileName);

private:
  bool
  parseVersionSection(std::shared_ptr<LasFile>& lasFile, std::size_t & lineNumber);

  void
  parseWellInformationSection(std::shared_ptr<LasFile>& lasFile,
                              std::size_t & lineNumber);

  void
  parseLogInformationSection(std::shared_ptr<LasFile>& lasFile,
                             std::size_t & lineNumber);

  void
  parseParameterInformationSection(std::shared_ptr<LasFile>& lasFile,
                                   std::size_t & lineNumber);

  void
  parseOtherInformationSection(std::shared_ptr<LasFile>& lasFile,
                               std::size_t & lineNumber);

  void
  parseAsciiLogDataSection(std::shared_ptr<LasFile>& lasFile, std::size_t & lineNumber);

  void
  parseLines(std::shared_ptr<LasFile>& lasFile);

private:
  std::vector<QString> _lines;

  int _version;
  bool _wrap;
};
}
}
